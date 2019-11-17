#include <unistd.h>
#include <stdio.h>
#include <getopt.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 4096
//#define BUFSIZE 256

#define USAGE                                                \
    "usage:\n"                                               \
    "  transferserver [options]\n"                           \
    "options:\n"                                             \
    "  -f                  Filename (Default: cs6200.txt)\n" \
    "  -h                  Show this help message\n"         \
    "  -p                  Port (Default: 6200)\n"

/* OPTIONS DESCRIPTOR ====================================================== */
static struct option gLongOptions[] = {
    {"filename", required_argument, NULL, 'f'},
    {"help", no_argument, NULL, 'h'},
    {"port", required_argument, NULL, 'p'},
    {NULL, 0, NULL, 0}};

int processreq(int, char*); /* handles client request */

int main(int argc, char **argv)
{
    int option_char;
    int portno = 6200;             /* port to listen on */
    char *filename = "cs6200.txt"; /* file to transfer */

    setbuf(stdout, NULL); // disable buffering

    // Parse and set command line arguments
    while ((option_char = getopt_long(argc, argv, "p:hf:x", gLongOptions, NULL)) != -1)
    {
        switch (option_char)
        {
        case 'p': // listen-port
            portno = atoi(optarg);
            break;
        default:
            fprintf(stderr, "%s", USAGE);
            exit(1);
        case 'h': // help
            fprintf(stdout, "%s", USAGE);
            exit(0);
            break;
        case 'f': // listen-port
            filename = optarg;
            break;
        }
    }


    if ((portno < 1025) || (portno > 65535))
    {
        fprintf(stderr, "%s @ %d: invalid port number (%d)\n", __FILE__, __LINE__, portno);
        exit(1);
    }
    
    if (NULL == filename)
    {
        fprintf(stderr, "%s @ %d: invalid filename\n", __FILE__, __LINE__);
        exit(1);
    }

    /* Socket Code Here */
  
  //initializations
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
  serv_addr.sin_port = htons(portno);
 
  //bind server socket to port
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
           fprintf(stderr,"ERROR on binding");

  //listen and lineup client traffic
  listen(sockfd,5);

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
  //fprintf(stdout,"Filename before %s\n",filename); 
  int retval = processreq(newsockfd, filename);
  fprintf(stdout,"Process returned %d\n",retval); 
  if (retval !=0) {
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
 return 0;
}

int processreq(int clientsockfd, char * filename)
{
  int num=0, filenum=0; //return value of read and write function
  int filefd; //file descriptor
  char buffer[BUFSIZE]; // memory space to read in/out of socket (n/w)

  //fprintf(stdout,"Filename %s\n",filename); //check number of bytes read
  //fprintf(stdout,"&Filename %d\n",*filename); //check number of bytes read

  //open file
  filefd = open((const char*)filename, S_IRUSR | S_IWUSR);
  if (filefd < 0) {
       fprintf(stderr,"ERROR opening file\n");
       return EXIT_FAILURE;
  }

  //read from file and send to client in chunks
  //while (1)
  //{  
     //reset memory before receiving message from client
     bzero(buffer,BUFSIZE);
     fprintf(stdout,"Buffer size %d\n",BUFSIZE); //number of bytes  in buffer
 
     //read from file
     //filenum = read(filefd,buffer,BUFSIZE);
     while((filenum = read(filefd,buffer,BUFSIZE))>0)
     {
     fprintf(stdout,"Start of read loop\n");
     fprintf(stdout,"Read bytes %d\n",filenum); //check number of bytes read
     
     //fprintf(stdout,"Read data %s\n",buffer); //print data chunk read from file
     if (filenum == -1) {
          fprintf(stderr,"ERROR reading from file\n");
          return EXIT_FAILURE;
     }
     if (filenum < 0) {
          fprintf(stderr,"ERROR reading from file\n");
          return EXIT_FAILURE;
     }
      if (filenum == 0) {
          fprintf(stdout,"End of file\n");
          break;
     }
     
     //send to client
     //while (num < filenum)
     //{
     //fprintf(stdout,"Start of copy loop\n");
     //num = send(clientsockfd,buffer,filenum, 0);
     while ((num = send(clientsockfd,buffer,filenum, 0))>0)
     {
     fprintf(stdout,"Start of send loop\n");
     fprintf(stdout,"Sent bytes %d\n",num); //check number of bytes sent
     if (num == -1) 
         break;
     if (num == 0) 
         break;
     if (num < 0) {
       fprintf(stderr,"ERROR writing to socket\n");
       return EXIT_FAILURE;
     }
     //fprintf(stdout,"Sent data %s\n",buffer);
     filenum = filenum-num;
     fprintf(stdout,"Remaining bytes %d\n",filenum);
     }
     fprintf(stdout,"End of send loop\n"); //end of copy loop
     } 
  fprintf(stdout,"End of read loop\n"); /* end of while */
  //close file
  close(filefd);
  return EXIT_SUCCESS;
}
