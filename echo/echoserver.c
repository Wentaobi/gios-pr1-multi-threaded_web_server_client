#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <getopt.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>

#define BUFSIZE 256

#define USAGE                                                                 \
"usage:\n"                                                                    \
"  echoserver [options]\n"                                                    \
"options:\n"                                                                  \
"  -p                  Port (Default: 6200)\n"                                \
"  -m                  Maximum pending connections (default: 1)\n"            \
"  -h                  Show this help message\n"                              \

/* OPTIONS DESCRIPTOR ====================================================== */
static struct option gLongOptions[] = {
  {"port",          required_argument,      NULL,           'p'},
  {"maxnpending",   required_argument,      NULL,           'm'},
  {"help",          no_argument,            NULL,           'h'},
  {NULL,            0,                      NULL,             0}
};

void processreq(int); //handles client request

int main(int argc, char **argv) {
  int option_char;
  int portno = 6200; /* port to listen on */
  int maxnpending = 1;

  // Parse and set command line arguments
  while ((option_char = getopt_long(argc, argv, "p:m:hx", gLongOptions, NULL)) != -1) {
   switch (option_char) {
      case 'p': // listen-port
        portno = atoi(optarg);
        break;
      default:
        fprintf(stderr, "%s ", USAGE);
        exit(1);
      case 'm': // server
        maxnpending = atoi(optarg);
        break;
      case 'h': // help
        fprintf(stdout, "%s ", USAGE);
        exit(0);
        break;
    }
  }

    setbuf(stdout, NULL); // disable buffering

    if ((portno < 1025) || (portno > 65535)) {
        fprintf(stderr, "%s @ %d: invalid port number (%d)\n", __FILE__, __LINE__, portno);
        exit(1);
    }
    if (maxnpending < 1) {
        fprintf(stderr, "%s @ %d: invalid pending count (%d)\n", __FILE__, __LINE__, maxnpending);
        exit(1);
    }


  /* Socket Code Here */

  //initializations
  int sockfd=0, newsockfd; //socket descriptors
  //int num; //return value of read and write function
  int  clilen, reuse, pid; 

  //char buffer[BUFSIZE]; // memory space to read in/out of socket (n/w)

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
  serv_addr.sin_port = htons(portno);
 
  //bind server socket to port
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
           fprintf(stderr,"ERROR on binding");

  //listen and lineup client traffic
  listen(sockfd,maxnpending);

  clilen = sizeof(cli_addr);
  
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
  processreq(newsockfd);
  exit(0);
   }
  else
  close(newsockfd);
  } //end of while
 close(sockfd); 
 return 0;
}

void processreq(int clientsockfd)
{
  int num; //return value of read and write function
  char buffer[BUFSIZE]; // memory space to read in/out of socket (n/w)

  //reset memory before receiving message from client
  bzero(buffer,BUFSIZE);
  
  //recv message from client
  //num = read(newsockfd,buffer,255);
  num = recv(clientsockfd,buffer,BUFSIZE, 0);
  if (num < 0) 
       fprintf(stderr,"ERROR reading from socket");
  
  //fprintf(stdout,"Received bytes %d\n",num); //check number of bytes received


  //fprintf(stdout, "Here is the message: %s\n",buffer);
  fprintf(stdout,"%s\n",buffer); //print message received from client

  //send message to client
  //n = write(newsockfd,"I got your message",18);
  //n = send(newsockfd,"I got your message",18, 0);
  num = send(clientsockfd,buffer,strlen(buffer), 0);
  if (num < 0) 
       fprintf(stderr,"ERROR writing to socket");
  //fprintf(stdout,"Sent bytes %d\n",num); //check number of bytes sent


}
