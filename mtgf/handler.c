#include <stdlib.h>
#include <fcntl.h>
#include <curl/curl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include "steque.h"
#include "gfserver.h"
#include "content.h"

#include "gfserver-student.h"

#define BUFFER_SIZE 6200
#define THREAD_NUM 100

pthread_t thread[THREAD_NUM];

pthread_mutex_t locktask;
pthread_mutex_t lockfile;

steque_t *steque;

int threadcount = 0;

typedef struct stequeitem{
	gfcontext_t *ctx;
	char *path;
	void *arg;
} stequeitem;

void dotask(int *thread);

void exit_threads(){
	fprintf(stdout, "*** START exiting threads ***\n");
	steque_destroy(steque);
	free(steque);
	fprintf(stdout, "*** SUCCESS exiting threads ***\n");
}

void req_threads(){
	fprintf(stdout, "*** START requesting threads ***\n");
	steque =malloc(sizeof(steque_t));
	steque_init(steque);
	if(pthread_mutex_init(&locktask, NULL) != 0){
		fprintf(stderr, "*** ERROR mutex init on task ***\n");
		exit(-1);
	}
	if(pthread_mutex_init(&lockfile, NULL) != 0){
		fprintf(stderr, "*** ERROR mutex init on file ***\n");
		exit(-1);
	}
	fprintf(stdout, "*** SUCCESS requesting threads ***\n");
}

void init_threads(int nthreads){

	threadcount = nthreads;
	int num, returncode=0;
	fprintf(stdout, "*** START initiating %d threads ***\n", nthreads);
	for(num=0; num<nthreads; num++){
		returncode = pthread_create(&(thread[num]),NULL, (void*)&dotask, &(thread[num]));
		if (returncode != 0) {
			fprintf(stderr, "*** ERROR initiating %dth thread ***\n", num);
			exit(-1);
    		}
    	fprintf(stdout, "*** SUCCESS initiating %dth thread ***\n", num);
	}

}

void dotask(int *thread){
	fprintf(stdout, "*** START task on %d thread ***\n", *thread);
	while(1){
		if (!steque_isempty(steque)){
			pthread_mutex_lock(&locktask);
			stequeitem* stqitm=steque_pop(steque);
			pthread_mutex_unlock(&locktask);
			int filedescriptor;
			ssize_t filelen, datalen=0, readlen, writelen;
			char buffer[BUFFER_SIZE];
			if (stqitm != NULL){
				filedescriptor=content_get(stqitm->path);
				if(filedescriptor<0){
				gfs_sendheader(stqitm->ctx, GF_FILE_NOT_FOUND, 0);
				continue;	
				}
				filelen=lseek(filedescriptor, 0, SEEK_END);
				gfs_sendheader(stqitm->ctx, GF_OK, filelen);
				pthread_mutex_lock(&lockfile);
				while(datalen<filelen){
					readlen=pread(filedescriptor, buffer, BUFFER_SIZE, datalen);
					if (readlen <= 0){
						gfs_abort(stqitm->ctx);
						exit(-1);
					}
					writelen = gfs_send(stqitm->ctx, buffer, readlen);
					datalen += writelen;
				}
				pthread_mutex_unlock(&lockfile);
				
			}
		}
		
	}	
	fprintf(stdout, "*** SUCCESS task on %d thread ***\n", *thread);
}



//
//  The purpose of this function is to handle a get request
//
//  The ctx is the "context" operation and it contains connection state
//  The path is the path being retrieved
//  The arg allows the registration of context that is passed into this routine.
//  Note: you don't need to use arg. The test code uses it in some cases, but
//        not in others.
//
ssize_t getfile_handler(gfcontext_t *ctx, char *path, void* arg){
	stequeitem* stq=malloc(sizeof(stequeitem));
	stq->ctx=ctx;
	stq->path=path;
	stq->arg=arg;
	steque_enqueue(steque, stq);
	return 0;
}

