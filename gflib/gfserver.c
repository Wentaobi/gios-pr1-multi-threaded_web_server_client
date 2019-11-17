#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>

#include "gfserver.h"
#include "gfserver-student.h"


/* 
 * Modify this file to implement the interface specified in
 * gfserver.h.
 */

#define BUFSIZE (5120)
#define HEADSIZE (512)

/* define members of gfcontext_t structure*/
typedef struct gfcontext_t {
	int socket_connection;
        int socket_server;
        
        char* filepath;
        size_t file_len;

        gfstatus_t status;

} gfcontext_t;

/* define members of gfserver_t structure*/
typedef struct gfserver_t {
	unsigned short port;
	int max_npending;
	char *path;

        gfcontext_t *ctx;
        void *handlerarg;
	ssize_t (*handler)(gfcontext_t *ctx, char *path, void *handlerarg);

} gfserver_t;

void gfs_abort(gfcontext_t *ctx){
fprintf(stdout, "*** START abort send ***\n");
close(ctx->socket_connection);
fprintf(stdout, "*** STOP abort send ***\n");
}

ssize_t gfs_send(gfcontext_t *ctx, void *data, size_t size){
fprintf(stdout, "*** START sending file chunk ***\n");
ssize_t num = send(ctx->socket_connection,data,size, 0);
if (num < 0)
      fprintf(stderr, "*** ERROR sending file chunk ***\n");
else
      fprintf(stdout, "*** SUCCESS sending file chunk ***\n");
return num;
}

gfserver_t* gfserver_create(){

      gfserver_t *gfs = malloc(sizeof(gfserver_t));
      return gfs;
}

ssize_t gfs_sendheader(gfcontext_t *ctx, gfstatus_t status, size_t file_len){
fprintf(stdout, "*** START sending header ***\n");
char header[HEADSIZE];
bzero(header, HEADSIZE);
char *message = "";

if (status == GF_OK) {
fprintf(stdout, "*** PASS scenario ***\n");
strncpy(message, "GETFILE OK %lu\r\n\r\n", file_len);
}


if (status == GF_ERROR || status == GF_FILE_NOT_FOUND) {
      fprintf(stdout, "sss*** FAIL scenario ***\n");
      if ( status == GF_FILE_NOT_FOUND)
      message = "GETFILE FILE_NOT_FOUND\rsssssssssss\n\r\n";
      else
      message = "GETFILE ERROR\r\n\r\n";
strncpy(header, message, strlen(message));
}

ssize_t num = send(ctx->socket_connection,header,(strlen(header)+1), 0);
if (num < 0)
      fprintf(stderr, "*** ERROR sending header ***\n");
else
      fprintf(stdout, "*** SUCCESS sending header ***\n");
return num;
}

void gfserver_serve(gfserver_t *gfs){

fprintf(stdout, "*** ENTER initialize server ***\n");

//initialize server

  int sockfd=0, newsockfd; //socket descriptors
  int  clilen, reuse, pid; 

  struct sockaddr_in serv_addr, cli_addr; //structures containing internet address

  //socket creation
  sockfd = socket(AF_INET, SOCK_STREAM, 0); //internet domain for TCP connection
  if (sockfd < 0)
     fprintf(stderr,"ERROR opening socket");

  //reuse socket
  if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1)
            fprintf(stderr,"ERROR on socket reuse");

  //reset struct values for server and initialize with new values
  bzero((char *) &serv_addr, sizeof(serv_addr)); 
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(gfs->port);

  //bind server socket to port
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
           fprintf(stderr,"ERROR on binding");

  //listen and lineup client traffic
  listen(sockfd,gfs->max_npending);

  fprintf(stdout, "*** SUCCESS initialize server ***\n");
  fprintf(stdout, "*** START queuing and serving  ***\n");

 while(1)
  {
  //accept client and prepare to receive/send
  newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen); //client socket descriptor
  if (newsockfd < 0)
       fprintf(stderr,"ERROR on accept");
   
  pid=fork();
  if (pid == 0) {
  close(sockfd);
  //process client request
  int retval = processreq(gfs, sockfd, newsockfd);
  fprintf(stdout,"Process returned %d\n",retval); 
  if (retval <1) {
      fprintf(stdout,"ERROR processing request\n"); 
      break;
  }    
  exit(0);
   }
  else
  close(newsockfd);
  } //end of while
 close(sockfd); 
 fprintf(stdout,"Connection closed\n"); 

}

void gfserver_set_handlerarg(gfserver_t *gfs, void* arg){

fprintf(stdout, "*** START setting handler argument in gfserver_t handle ***\n");
gfs->handlerarg =malloc(sizeof(arg));
gfs->handlerarg = arg;
fprintf(stdout, "*** SUCCESS setting handler argument in gfserver_t handle ***\n");

}

void gfserver_set_handler(gfserver_t *gfs, ssize_t (*handler)(gfcontext_t *, char *, void*)){

fprintf(stdout, "*** START setting handler in gfserver_t handle ***\n");
gfs->handler = handler;
fprintf(stdout, "*** SUCCESS setting handler in gfserver_t handle ***\n");

}

void gfserver_set_maxpending(gfserver_t *gfs, int max_npending){

fprintf(stdout, "*** START setting value of max number pending: %d in gfserver_t handle ***\n", max_npending);
gfs->max_npending = max_npending;
fprintf(stdout, "*** SUCCESS setting value of max number pending: %d in gfserver_t handle ***\n", max_npending);
}

void gfserver_set_port(gfserver_t *gfs, unsigned short port){

fprintf(stdout, "*** START setting value of port: %u in gfserver_t handle ***\n", port);
gfs->port = port;
fprintf(stdout, "*** SUCCESS setting value of port: %u in gfserver_t handle ***\n", port);

}

/*
 * support functions
 */

int processreq(gfserver_t *gfs, int serversockfd, int clientsockfd){
  fprintf(stdout,"*** START processing request ***\n"); 
  int num=0; //return value of read and write function
  char buffer[BUFSIZE]; // memory space to read in/out of socket (n/w)
  char header[HEADSIZE]; // memory space to read in/out of socket (n/w)
  char *scheme;
  char *method;
  char *filename;
  char *message;
  bzero(buffer,BUFSIZE);
  bzero(header,HEADSIZE);

  fprintf(stdout,"*** Buffer size %d ***\n",BUFSIZE); //number of bytes  in buffer
 
  num = recv(clientsockfd,buffer,BUFSIZE, 0);
  if (num < 0) 
       fprintf(stderr,"*** ERROR processing request ***\n");
else
       fprintf(stdout,"*** SUCCESS processing request ***\n");

 scheme = strtok(buffer, " ");
 method = strtok(NULL, " ");
 filename = strtok(NULL, " ");

 gfcontext_t *ctx = malloc(sizeof(gfcontext_t));
 
 ctx->filepath = filename;
 ctx->socket_server = serversockfd;
 ctx->socket_connection = clientsockfd;

 if(scheme == NULL || method == NULL || filename == NULL || strcmp(scheme, "GETFILE") != 0 || strcmp(method, "GET") != 0){
 message = "GETFILE FILE_NOT_FOUND\r\n\r\n";
 strncpy(header, message, strlen(message));
 int sendnum = send(ctx->socket_connection, header, strlen(header)+1, 0);
if (sendnum < 0) 
       fprintf(stderr,"*** ERROR processing request ***\n");
else
       fprintf(stdout,"*** SUCCESS processing request ***\n");
} else
gfs->handler(ctx, filename, gfs->handlerarg);
 
return num;
}


