/*
 *  This file is for use by students to define anything they wish.  It is used by the gf client implementation
 */
 #ifndef __GF_CLIENT_STUDENT_H__
 #define __GF_CLIENT_STUDENT_H__
 
 #include "gf-student.h"
 #include "gfclient.h"

/*
 * returns socket file descriptor after successful connection to server
 */
int connect_server(char *server, unsigned short port);

/*
 * returns the buffer string to be sent to as request to server
 */
char* request_buffer(gfcrequest_t *gfr);

/*
 * process response received
 */
//void process_response(gfcrequest_t *gfr, int header_flag, char response_buffer);

 #endif // __GF_CLIENT_STUDENT_H__
