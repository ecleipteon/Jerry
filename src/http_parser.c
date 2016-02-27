/*
 ============================================================================
 Name        : http_parse.c
 Author      : Luca Maria Castiglione
 Version     : 0.1
 Copyright   : This file is part of FraWs released under GNU/GPL v 2 license
 Description : FraWs 0.1
 ============================================================================
 */


#include "headers/http_parser.h"


http_t *parse(const char *req, http_t *request)
{
	char 	buffer[MAX];
	char	*tmp, *tmp2;

	tmp2 = tmp = strchr(req, ' ');

	strncpy(buffer, req, tmp-req);

	if((strcmp(buffer, "GET")) == 0)
		request->type=GET;
	/*TODO: implementare per post, head etc, etc*/

	tmp++;
	tmp2 = strchr(tmp+1, ' ');

	strncpy(buffer, tmp, tmp2-tmp);
	buffer[(tmp2-tmp)] =  '\0';

	if(strcmp(buffer, "/") == 0)
		strcpy(request->doc, "www/index.html");
	else {
		strcpy(request->doc, "www/");
		strncat(request->doc, buffer+1, SIZE);
	}


	printf("Letto: %s\n", request->doc);



	request->status = CLOSE;

	strcpy(request->user_agent, "dottore");



	return request;

}



