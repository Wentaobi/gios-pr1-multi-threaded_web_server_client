#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <getopt.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 256

#define USAGE                                                \
    "usage:\n"                                               \
    "  transferclient [options]\n"                           \
    "options:\n"                                             \
    "  -s                  Server (Default: localhost)\n"    \
    "  -p                  Port (Default: 6200)\n"           \
    "  -o                  Output file (Default 6200.txt)\n" \
    "  -h                  Show this help message\n"

/* OPTIONS DESCRIPTOR ====================================================== */
static struct option gLongOptions[] = {
    {"server", required_argument, NULL, 's'},
    {"port", required_argument, NULL, 'p'},
    {"output", required_argument, NULL, 'o'},
    {"help", no_argument, NULL, 'h'},
    {NULL, 0, NULL, 0}};

/* Main ========================================================= */
int main(int argc, char **argv)
{
    int option_char = 0;
    char *hostname = "localhost";
    unsigned short portno = 6200;
    char *filename = "6200.txt";

    setbuf(stdout, NULL);

    // Parse and set command line arguments
    while ((option_char = getopt_long(argc, argv, "s:p:o:hx", gLongOptions, NULL)) != -1)
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
        case 'o': // filename
            filename = optarg;
            break;
        case 'h': // help
            fprintf(stdout, "%s", USAGE);
            exit(0);
            break;
        }
    }

    if (NULL == hostname)
    {
        fprintf(stderr, "%s @ %d: invalid host name\n", __FILE__, __LINE__);
        exit(1);
    }

    if (NULL == filename)
    {
        fprintf(stderr, "%s @ %d: invalid filename\n", __FILE__, __LINE__);
        exit(1);
    }

    if ((portno < 1025) || (portno > 65535))
    {
        fprintf(stderr, "%s @ %d: invalid port number (%d)\n", __FILE__, __LINE__, portno);
        exit(1);
    }

    /* Socket Code Here */

    //initializations 
    int sockfd=0, filefd; //socket descriptor
    int num,filenum=0; //return value of read and write function

    char buffer[BUFSIZE]; // memory space to read in/out of socket (n/w)


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

    //fprintf(stdout,"Filename %s\n",filename); 
    //fprintf(stdout,"*Filename %d\n",*filename); 
    //fprintf(stdout,"&Filename %s\n",&filename); 

    //open file
    filefd = open((const char*) filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (filefd < 0) {
         fprintf(stderr,"ERROR opening file\n");
         exit(EXIT_FAILURE);
    }
  
    //receive message from server
    //do {
    //reset memory to receive message from server
    bzero(buffer,BUFSIZE);
    fprintf(stdout,"Buffer size %d\n",BUFSIZE); //number of bytes  in buffer
    
    //receive message from server   
    while ((num = recv(sockfd,buffer,BUFSIZE, 0)) > 0)
    {   
    fprintf(stdout,"Received bytes %d\n",num); 
    //fprintf(stdout,"Received data %s\n",buffer);
    if (num == -1) 
        break;
    if (num == 0) 
        break;
    if (num < 0) {
         fprintf(stderr, "ERROR reading from socket\n");
         exit(EXIT_FAILURE);
    }

    //write message to file
    //while (num>filenum) {
    //filenum = write(filefd,buffer,num);
     while ((filenum = write(filefd,buffer,num))>0)
     {
    
    //fprintf(stdout,"Written bytes %d\n",filefd); 
    fprintf(stdout,"Written bytes %d\n",filenum); 
    //fprintf(stdout,"Written data %s\n",buffer); 
    if (filenum == -1)
         break;
    if (filenum < 0) {
         fprintf(stderr, "ERROR writing to socket\n");
         exit(EXIT_FAILURE);
    }
    num = num - filenum;
    fprintf(stdout,"Remaining bytes %d\n",num);
    } /* end of while */
    } /* end of while */

    //close file
    close(filefd);

    //close socket
    close(sockfd);
    return 0;
}
