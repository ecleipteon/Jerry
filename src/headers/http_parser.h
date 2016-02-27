/*
 ============================================================================
 Name        : http_parse.h
 Author      : Luca Maria Castiglione
 Version     : 0.1
 Copyright   : This file is part of FraWs released under GNU/GPL v 2 license
 Description : FraWs 0.1
 ============================================================================
 */

#ifndef _HTTP_PARSER_H
#define _HTTP_PARSER_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define	SIZE	100
#define MAX		2048

#define	GET		0
#define POST 	1
#define HEAD	2

#define CLOSE	0
#define KEEPAL	1

typedef struct http_t {
	int		type;
	int 	version;
	char 	doc[SIZE];
	int		status;
	char 	user_agent[SIZE];
	int		connection;
	int 	length;

}http_t;


http_t *parse(const char *request, http_t *hrequest);

#endif /*_HTTP_PARSER_H*/
