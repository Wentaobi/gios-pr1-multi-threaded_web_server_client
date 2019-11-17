/*
 *  This file is for use by students to define anything they wish.  It is used by the gf server implementation
 */
#ifndef __GF_SERVER_STUDENT_H__
#define __GF_SERVER_STUDENT_H__

#include "gf-student.h"

/*
 * returns result after processing request
 */

int processreq(gfserver_t *gfs, int serversockfd, int clientsockfd);

#endif // __GF_SERVER_STUDENT_H__
