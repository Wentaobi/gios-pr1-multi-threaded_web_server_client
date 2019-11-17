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

#include "gfclient.h"
#include "gfclient-student.h"

#define BUFSIZE (5120)

/* define members of gfcrequest_t structure*/
typedef struct gfcrequest_t {
    char *server;
    unsigned short port;
 
    char *scheme;
    char *method;
    char *path;
    char *marker;

    size_t receivedbytes;

    size_t filelen;

    void (*headerfunc)(void*, size_t, void *);
    void *headerarg;

    void (*writefunc)(void*, size_t, void *);
    void *writearg;

    gfstatus_t status;
    
    void *header;
    size_t headerlength;
    void *filecontent;
    size_t filecontentlength;

 } gfcrequest_t;

void gfc_cleanup(gfcrequest_t *gfr){

}

gfcrequest_t *gfc_create(){
     
    gfcrequest_t *gfr = malloc(sizeof(gfcrequest_t));
    gfr->scheme = "GETFILE";
    gfr->method ="GET";
    gfr->marker = "\r\n\r\n";
    return gfr;

}

size_t gfc_get_bytesreceived(gfcrequest_t *gfr){

fprintf(stdout, "*** START getting value of bytes received from gfcrequest_t handle ***\n");
size_t receivedbytes = gfr->receivedbytes;
fprintf(stdout, "*** SUCCESS getting value of bytes received from gfcrequest_t handle ***\n");
return receivedbytes;
}

size_t gfc_get_filelen(gfcrequest_t *gfr){

fprintf(stdout, "*** START getting value of file length from gfcrequest_t handle ***\n");
size_t filelen = gfr->filelen;
fprintf(stdout, "*** SUCCESS getting value of file length from gfcrequest_t handle ***\n");
return filelen;
}

gfstatus_t gfc_get_status(gfcrequest_t *gfr){

fprintf(stdout, "*** START getting value of status from gfcrequest_t handle ***\n");
gfstatus_t status = gfr->status;
fprintf(stdout, "*** SUCCESS getting value of status: %d from gfcrequest_t handle ***\n", status);
return status;
}

void gfc_global_init(){
//not using any global variable since program will run on single thread
}

void gfc_global_cleanup(){
}

int gfc_perform(gfcrequest_t *gfr){

// make connection to server
fprintf(stdout, "*** START connecting to server ***\n");
int sockfd = connect_server(gfr->server, gfr->port);
fprintf(stdout, "*** SUCCESS connecting to server ***\n");

//prepare request
char* request_buffer_str = request_buffer(gfr);
fprintf(stdout, "*** Request_buffer: %s ***\n", request_buffer_str);

//send request to server
fprintf(stdout, "*** START sending request to server ***\n");
int num_req = send(sockfd, request_buffer_str, strlen(request_buffer_str), 0);
if (num_req < 0){
   fprintf(stderr, "ERROR writing to socket");
   exit(1);
}
else {
   fprintf(stdout,"*** Sent bytes %d\n ***",num_req); 
   fprintf(stdout, "*** SUCCESS sending request to server ***\n");
}

//receive response from server
fprintf(stdout, "*** START receiving response from server ***\n");
char res_buffer[BUFSIZE];
int num_res, recvtotalbytes=0, header_flag=1;
int *header_flag_pointer = &header_flag;
bzero(res_buffer,BUFSIZE);
while ((num_res = recv(sockfd,res_buffer,BUFSIZE, 0)) > 0)
    {   
    fprintf(stdout,"*** Received total bytes %d ***\n",recvtotalbytes); 
    fprintf(stdout,"*** Received bytes %d ***\n",num_res); 
    recvtotalbytes = recvtotalbytes + num_res;
    gfr->receivedbytes = recvtotalbytes;

    if (num_res == -1) 
        //break;
        exit(1);
    if (num_res == 0) 
        //break;
        exit(1);
    if (num_res < 0) {
         fprintf(stderr, "*** ERROR reading from socket ***\n");
         exit(1);
    }

	//process response
	//process_response(gfr, *header_flag_pointer, (char*)res_buffer);

char * response_buffer_str = (char *) malloc(gfr->receivedbytes + 1); 
	strcpy(response_buffer_str, res_buffer);
       
        if (*header_flag_pointer == 1) {

	char * checkheader = (char *) malloc(strlen(response_buffer_str) + 1); 
        strcpy(checkheader, response_buffer_str); 

	char *scheme = strtok(checkheader, " "); 
	char *status = strtok(NULL, " ");
	
        if (strcmp(scheme, "GETFILE") != 0) { 
              gfr->status = GF_INVALID; 
              fprintf(stderr, "*** ERROR INVALID header ***\n");
              exit(1);
        } 

       if ((strcmp(scheme, "GETFILE") == 0)&&(strcmp(status, "OK") != 0) ) { 
              gfr->status = GF_FILE_NOT_FOUND;
              fprintf(stderr, "*** ERROR File not found ***\n");
              exit(1);
        }

       if ((strcmp(scheme, "GETFILE") == 0)&&(strcmp(status, "OK") == 0) ) { 
              char *filelength = strtok(strtok(NULL, " "), "\r\n\r\n");
              fprintf(stdout, "*** Scheme is %s, Status is %s, File length is %s ***\n", scheme, status, filelength);
              gfr->status = GF_OK; 
              gfr->filelen = atol(filelength);
              *header_flag_pointer = 0;
              char *filecontent = strtok(NULL, "\r\n\r\n");
              
              char* header = (char*)malloc(strlen(scheme) + 1 + strlen(status) + 1 + strlen(filelength) + 6);
              strcpy(header, "GETFILE OK ");
              strcat(header, filelength);
              strcat(header, " \r\n\r\n");
              
              gfr->header=header;
              gfr->headerlength=strlen(header);
              gfr->filecontent=filecontent;
              gfr->filecontentlength=strlen(filecontent);

              gfr->headerfunc(gfr->header, gfr->headerlength, gfr->headerarg);
              gfr->writefunc(gfr->filecontent, gfr->filecontentlength, gfr->writearg);

              fprintf(stdout, "*** SUCCESS File transfer done ***\n");
              
        }
     } 
          gfr->writefunc(response_buffer_str, strlen(response_buffer_str), gfr->writearg);  
          
           fprintf(stdout, "*** SUCCESS File transfer done ***\n");
}

fprintf(stdout, "*** SUCCESS receiving response from server ***\n");
close(sockfd);
return(0);
}

void gfc_set_headerarg(gfcrequest_t *gfr, void *headerarg){

fprintf(stdout, "*** START setting header argument in gfcrequest_t handle ***\n");
gfr->headerarg =malloc(sizeof(headerarg));
gfr->headerarg =headerarg;
fprintf(stdout, "*** SUCCESS setting header argument in gfcrequest_t handle ***\n");
}

void gfc_set_headerfunc(gfcrequest_t *gfr, void (*headerfunc)(void*, size_t, void *)){

fprintf(stdout, "*** START setting header function in gfcrequest_t handle ***\n");
gfr->headerfunc=headerfunc;
fprintf(stdout, "*** SUCCESS setting header function in gfcrequest_t handle ***\n");
}

void gfc_set_path(gfcrequest_t *gfr, char* path){

fprintf(stdout, "*** START setting value of file path: %s in gfcrequest_t handle ***\n", path);

if (path != NULL) {
      gfr->path = (char*)malloc(sizeof(char)*(strlen(path)+1));
      strcpy(gfr->path, path);
      fprintf(stdout, "*** SUCCESS setting value of file path: %s in gfcrequest_t handle ***\n", path);
   }else {
      fprintf(stderr, "*** ERROR setting value of file-path: %s in gfcrequest_t handle ***\n", path);
	  exit(1);
   }

}

void gfc_set_port(gfcrequest_t *gfr, unsigned short port){

fprintf(stdout, "*** START setting value of port: %u in gfcrequest_t handle ***\n", port);
gfr->port = port;
fprintf(stdout, "*** SUCCESS setting value of port: %u in gfcrequest_t handle ***\n", port);
}

void gfc_set_server(gfcrequest_t *gfr, char* server){

fprintf(stdout, "*** START setting value of server: %s in gfcrequest_t handle ***\n", server);

if (server != NULL) {
      gfr->server = (char*)malloc(sizeof(char)*(strlen(server)+1));
      strcpy(gfr->server, server);
      fprintf(stdout, "*** SUCCESS setting value of server: %s in gfcrequest_t handle ***\n", server);
   }else {
      fprintf(stderr, "*** ERROR setting value of server: %s in gfcrequest_t handle ***\n", server);
	  exit(1);
   }
}

void gfc_set_writearg(gfcrequest_t *gfr, void *writearg){

fprintf(stdout, "*** START setting write argument in gfcrequest_t handle ***\n");
gfr->writearg =malloc(sizeof(writearg));
gfr->writearg =writearg;
fprintf(stdout, "*** SUCCESS setting write argument in gfcrequest_t handle ***\n");

}

void gfc_set_writefunc(gfcrequest_t *gfr, void (*writefunc)(void*, size_t, void *)){

fprintf(stdout, "*** START setting write function in gfcrequest_t handle ***\n");
gfr->writefunc=writefunc;
fprintf(stdout, "*** SUCCESS setting write function in gfcrequest_t handle ***\n");  
}

char* gfc_strstatus(gfstatus_t status){
    
    char * status_str;

    fprintf(stdout, "*** START processing status code: %d ***\n", status);

    switch(status) {
    case GF_OK:
         status_str = "OK";
    case GF_INVALID:
         status_str = "INVALID"; //header 
    case GF_FILE_NOT_FOUND:
         status_str = "FILE_NOT_FOUND"; //client error
    case GF_ERROR:
         status_str = "ERROR"; //server error
    default: 
         status_str = "UNKNOWN_ERROR"; //unhandled error 
    }

    fprintf(stdout, "*** SUCCESS processing status code: %d, status string is: %s ***\n", status, status_str);

    return status_str;
}

/*
 * support functions
 */

int connect_server(char *hostname, unsigned short portno){

    fprintf(stdout, "*** ENTER connect_server ***\n");

    //initializations 
    int sockfd=0; //socket descriptor
    //int num; //return value of read and write function


    struct sockaddr_in serv_addr; //structures containing internet address
    struct hostent *server;
     
    //socket creation
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //internet domain for TCP connection
    if (sockfd < 0)
        fprintf(stderr, "ERROR opening socket\n");

    server = gethostbyname(hostname); //server to connect to
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    
    //reset struct values for server and initialize with new values
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    //connect to server - send request and wait
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        fprintf(stderr, "ERROR connecting\n");
   
    fprintf(stdout, "*** EXIT connect_server ***\n");

    return sockfd;
}

char* request_buffer(gfcrequest_t *gfr){

    fprintf(stdout, "*** ENTER request_buffer ***\n");

    char *scheme = gfr->scheme;
    char *method = gfr->method;
    char *path = gfr->path;
    char *marker = gfr->marker;

    int request_buffer_len = sizeof(char)*(strlen(scheme)+strlen(method)+strlen(path)+strlen(marker) +3);
    char * request_buffer = (char *)malloc(request_buffer_len);

    strcpy(request_buffer, scheme);
    strcpy(request_buffer, " ");
    strcpy(request_buffer, method);
    strcpy(request_buffer, " ");
    strcpy(request_buffer, path);
    strcpy(request_buffer, marker);

    fprintf(stdout, "*** request_buffer: %s and request_buffer_len: %d ***\n",request_buffer, request_buffer_len);

    fprintf(stdout, "*** EXIT request_buffer ***\n");
    return request_buffer;
}

//void process_response(gfcrequest_t *gfr, int* header_flag_pointer, char res_buffer){
//}
    


