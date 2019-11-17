#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/* Be prepared accept a response of this length */
#define BUFSIZE 16

#define USAGE                                                                       \
    "usage:\n"                                                                      \
    "  echoclient [options]\n"                                                      \
    "options:\n"                                                                    \
    "  -s                  Server (Default: localhost)\n"                           \
    "  -p                  Port (Default: 6200)\n"                                  \
    "  -m                  Message to send to server (Default: \"hello world.\")\n" \
    "  -h                  Show this help message\n"

/* OPTIONS DESCRIPTOR ====================================================== */
static struct option gLongOptions[] = {
    {"server", required_argument, NULL, 's'},
    {"port", required_argument, NULL, 'p'},
    {"message", required_argument, NULL, 'm'},
    {"help", no_argument, NULL, 'h'},
    {NULL, 0, NULL, 0}};

/* Main ========================================================= */
int main(int argc, char **argv)
{
    int option_char = 0;
    char *hostname = "localhost";
    unsigned short portno = 6200;
    char *message = "Hello world!!";

    // Parse and set command line arguments
    while ((option_char = getopt_long(argc, argv, "s:p:m:hx", gLongOptions, NULL)) != -1)
    {
        switch (option_char)
        {
        case 's': // server
            hostname = optarg;
            break;
        case 'p': // listen-port
            portno = atoi(optarg);
            break;
        default:
            fprintf(stderr, "%s", USAGE);
            exit(1);
        case 'm': // message
            message = optarg;
            break;
        case 'h': // help
            fprintf(stdout, "%s", USAGE);
            exit(0);
            break;
        }
    }

    setbuf(stdout, NULL); // disable buffering

    if ((portno < 1025) || (portno > 65535))
    {
        fprintf(stderr, "%s @ %d: invalid port number (%d)\n", __FILE__, __LINE__, portno);
        exit(1);
    }

    if (NULL == message)
    {
        fprintf(stderr, "%s @ %d: invalid message\n", __FILE__, __LINE__);
        exit(1);
    }

    if (NULL == hostname)
    {
        fprintf(stderr, "%s @ %d: invalid host name\n", __FILE__, __LINE__);
        exit(1);
    }

    /* Socket Code Here */
    
    //initializations 
    int sockfd=0; //socket descriptor
    int num; //return value of read and write function

    char buffersend[BUFSIZE]; // memory space to read in/out of socket (n/w)
    char bufferrecv[BUFSIZE]; // memory space to read in/out of socket (n/w)

    struct sockaddr_in serv_addr; //structures containing internet address
    struct hostent *server;
     
    //socket creation
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //internet domain for TCP connection
    if (sockfd < 0)
        fprintf(stderr, "ERROR opening socket");

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
        fprintf(stderr, "ERROR connecting");
    
    //prepare message to be sent to server
    //printf("Please enter the message: ");
    bzero(buffersend,BUFSIZE);
    //fgets(buffer,BUFSIZE-1,stdin);
    strncpy(buffersend, message, BUFSIZE);
   
    //num = write(sockfd,buffer,strlen(buffer));
    num = send(sockfd,buffersend,strlen(buffersend),0);  //send message to server
    if (num < 0)
         fprintf(stderr, "ERROR writing to socket");
    
    //fprintf(stdout,"Sent bytes %d\n",num); //check number of bytes sent
    
    //reset memory to receive message from server
    bzero(bufferrecv,BUFSIZE);
  
    //n = read(sockfd,buffer,255);
    num = recv(sockfd,bufferrecv,BUFSIZE, 0);   //receive message from server
    if (num < 0)
         fprintf(stderr, "ERROR reading from socket");

    //fprintf(stdout,"Received bytes %d\n",num); //check number of bytes received
    //buffer[num] = '\0';
    fprintf(stdout,"%s\n",bufferrecv);

    //close socket
    close(sockfd);
    return 0;

}
