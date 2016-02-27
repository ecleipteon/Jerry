/*
 ============================================================================
 Name        : http_core.h
 Author      : Luca Maria Castiglione
 Version     : 0.1
 Copyright   : This file is part of FraWs released under GNU/GPL v 2 license
 Description : FraWs 0.1
 ============================================================================
 */

#ifndef HTTP_CORE_H
#define HTTP_CORE_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#include "http_parser.h"

#define HEADER "%s %s\nDate: %s\nServer: %s\nLast-Modified: %s\nContent-Type: %s\nContent-Length: %d \nAccept-Ranges: bytes\nConnection: %s\n\n"

#define VERSION "HTTP/1.1"

#define OK		"200 OK"
#define NF		"404 Not Found"

#define DATE	"Mon, 23 May 2005 22:38:34 GMT"
#define SERVER	"FraWS 0.1(Unix)"
#define LASTMOD	"Wed, 08 Jan 2003 23:11:55 GMT"
#define TYPE	"text/html; charset=UTF-8"
#define CONN	"close"



size_t 	responde(http_t *req, char * resp);
void 	*menage_conn(void *d);


#endif /*HTTP_CORE_H*/
