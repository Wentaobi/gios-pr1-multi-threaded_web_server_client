#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <getopt.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netdb.h>
#include <pthread.h>
#include "gfclient.h"
#include "workload.h"
#include "gfclient-student.h"
#include "steque.h"

#define USAGE                                                                 \
"usage:\n"                                                                    \
"  webclient [options]\n"                                                     \
"options:\n"                                                                  \
"  -h                  Show this help message\n"                              \
"  -n [num_requests]   Requests download per thread (Default: 4)\n"           \
"  -p [server_port]    Server port (Default: 6200)\n"                         \
"  -s [server_addr]    Server address (Default: 127.0.0.1)\n"                   \
"  -t [nthreads]       Number of threads (Default 4)\n"                       \
"  -w [workload_path]  Path to workload file (Default: workload.txt)\n"       \

#define THREAD_NUM 100
#define BUFF_NUM 512

pthread_t thread[THREAD_NUM];

pthread_mutex_t lockfile;

/* OPTIONS DESCRIPTOR ====================================================== */
static struct option gLongOptions[] = {
  {"help",          no_argument,            NULL,           'h'},
  {"nthreads",      required_argument,      NULL,           't'},
  {"nrequests",     required_argument,      NULL,           'n'},
  {"server",        required_argument,      NULL,           's'},
  {"port",          required_argument,      NULL,           'p'},
  {"workload-path", required_argument,      NULL,           'w'},
  {NULL,            0,                      NULL,             0}
};

typedef struct serverthread{
	char *server;
	unsigned short port;
	int requestcount;
	int threadid;
}serverthread;

void dotask(serverthread *taskthread);

static void Usage() {
	fprintf(stdout, "%s", USAGE);
}

static void localPath(char *req_path, char *local_path){
  static int counter = 0;

  sprintf(local_path, "%s-%06d", &req_path[1], counter++);
}

static FILE* openFile(char *path){
  char *cur, *prev;
  FILE *ans;

  /* Make the directory if it isn't there */
  prev = path;
  while(NULL != (cur = strchr(prev+1, '/'))){
    *cur = '\0';

    if (0 > mkdir(&path[0], S_IRWXU)){
      if (errno != EEXIST){
        perror("Unable to create directory");
        exit(EXIT_FAILURE);
      }
    }

    *cur = '/';
    prev = cur;
  }

  if( NULL == (ans = fopen(&path[0], "w"))){
    perror("Unable to open file");
    exit(EXIT_FAILURE);
  }

  return ans;
}

/* Callbacks ========================================================= */
static void writecb(void* data, size_t data_len, void *arg){
  FILE *file = (FILE*) arg;

  fwrite(data, 1, data_len, file);
}

void dotask(serverthread *taskthread){
	fprintf(stdout, "*** START requesting threads ***\n");
	int num;
	gfcrequest_t *gfr = NULL;
	for(num=0; num<taskthread->requestcount; num++){
		char *path=workload_get_path();
		if (path == NULL){
			fprintf(stderr, "*** ERROR processing file path ***\n");
			exit(-1);
		}
		FILE *file;
		char localpath[BUFF_NUM];
		int returncode;
		localPath(path, localpath);
		pthread_mutex_lock(&lockfile);
		file = openFile(localpath);
		gfr = gfc_create();
    		gfc_set_server(gfr, taskthread->server);
    		gfc_set_path(gfr, path);
    		gfc_set_port(gfr, taskthread->port);
    		gfc_set_writefunc(gfr, writecb);
    		gfc_set_writearg(gfr, file);

    		fprintf(stdout, "Requesting %s%s\n", taskthread->server, path);

    		if ( 0 > (returncode = gfc_perform(gfr))){
      			fprintf(stdout, "gfc_perform returned an error %d\n", returncode);
      			fclose(file);
      			if ( 0 > unlink(localpath))
        		fprintf(stderr, "unlink failed on %s\n", localpath);
    		}
    		else {
        		fclose(file);
    		}
		pthread_mutex_unlock(&lockfile);

    		if ( gfc_get_status(gfr) != GF_OK){
      			if ( 0 > unlink(localpath))
        			fprintf(stderr, "unlink failed on %s\n", localpath);
    			}

   		fprintf(stdout, "Status: %s\n", gfc_strstatus(gfc_get_status(gfr)));
    		fprintf(stdout, "Received %zu of %zu bytes\n", gfc_get_bytesreceived(gfr), gfc_get_filelen(gfr));

    		gfc_cleanup(gfr);

		}
	pthread_exit(NULL);
	free(taskthread);
	fprintf(stdout, "*** SUCCESS requesting threads ***\n");
}

/* Main ========================================================= */
int main(int argc, char **argv) {
/* COMMAND LINE OPTIONS ============================================= */
  char *server = "localhost";
  unsigned short port = 6200;
  char *workload_path = "workload.txt";

  int i = 0;
  int option_char = 0;
  int nrequests = 4;
  int nthreads = 4;
  int returncode = 0;
  //gfcrequest_t *gfr = NULL;
  //FILE *file = NULL;
  //char *req_path = NULL;
  //char local_path[1024];

  setbuf(stdout, NULL); // disable caching

  // Parse and set command line arguments
  while ((option_char = getopt_long(argc, argv, "hn:p:s:t:w:x", gLongOptions, NULL)) != -1) {
    switch (option_char) {
      case 'h': // help
        Usage();
        exit(0);
        break;                      
      case 'n': // nrequests
        nrequests = atoi(optarg);
        break;
      case 'p': // port
        port = atoi(optarg);
        break;
      default:
        Usage();
        exit(1);
      case 's': // server
        server = optarg;
        break;
      case 't': // nthreads
        nthreads = atoi(optarg);
        break;
      case 'w': // workload-path
        workload_path = optarg;
        break;
    }
  }

  if( EXIT_SUCCESS != workload_init(workload_path)){
    fprintf(stderr, "Unable to load workload file %s.\n", workload_path);
    exit(EXIT_FAILURE);
  }

  gfc_global_init();

  /*Making the requests...*/
  /*for(i = 0; i < nrequests * nthreads; i++){
    req_path = workload_get_path();

    if(strlen(req_path) > 512){
      fprintf(stderr, "Request path exceeded maximum of 512 characters\n.");
      exit(EXIT_FAILURE);
    }*/

    if(pthread_mutex_init(&lockfile, NULL) != 0){
		fprintf(stderr, "*** ERROR mutex init on file ***\n");
		exit(-1);
    }

    for(i=0; i<nrequests; i++){
    	serverthread *sthread = malloc(sizeof(serverthread));
	sthread->server = server;
	sthread->port = port;
	sthread->requestcount = nthreads;
	sthread->threadid = thread[i];
	returncode = pthread_create(&(thread[i]),NULL, (void*)&dotask, sthread);
		if (returncode != 0) {
			fprintf(stderr, "*** ERROR initiating %dth thread ***\n", i);
			exit(-1);
    		}
	}
    for(i=0; i>nrequests; i++){
	pthread_join(thread[i], NULL);
    }

  //}

  gfc_global_cleanup();

  return 0;
}  
