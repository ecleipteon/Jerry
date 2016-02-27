/*
 ============================================================================
 Name        : http_core.c
 Author      : Luca Maria Castiglione
 Version     : 0.1
 Copyright   : This file is part of FraWs released under GNU/GPL v 2 license
 Description : FraWs 0.1
 ============================================================================
 */


#include "headers/http_core.h"
#include "headers/http_parser.h"

static int counter = 0; /*Used as counter. Incremented by one for each connection*/


void *menage_conn(void *d)
{
	char buff[5012];
	char res[5012];
	int *sd_client;
	http_t tmp;

	//tmp = (http_t *) malloc(sizeof(http_t));



	sd_client = (void *) d;
	recv(*sd_client, buff, sizeof(buff), 0);

	printf("Connessione %d\n", counter++);

	parse(buff, &tmp);

	responde(&tmp, res);

	/*buff[0]='\0';
	sprintf(buff, HEADER, len);
	strcat(buff, RESPONSE);
	//printf("%s", buff);
	 */

	send(*sd_client, res, strlen(res), 0);


	close(*sd_client);
	free(sd_client);


	return NULL;
}


size_t 	responde(http_t *req, char * resp)
{
	int len = 0;
	char tmp[5012];
	char c;

	FILE *page;

	page = fopen(req->doc, "r");


	if(page == NULL) {
		strcpy(tmp,"404, Page not found");
		len = strlen(tmp);
		sprintf(resp, HEADER, VERSION,NF, DATE, SERVER, LASTMOD, TYPE, len, CONN);

	}
	else {
		while ( (c=fgetc(page))!= EOF && len < 5012)
			tmp[len++]= c;

		tmp[len] = '\0';

		fclose(page);
		sprintf(resp, HEADER, VERSION,OK, DATE, SERVER, LASTMOD, TYPE, len, CONN );
	}

	strcat(resp, tmp);

	return len;
}
