/*
 ============================================================================
 Name        : Jerry.c
 Author      : Luca Maria Castiglione
 Version     : 0.1
 Copyright   : Released under GPL
 Description : FraWs 0.1
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>


#include "headers/http_core.h"
#include "headers/http_parser.h"
#include "headers/pool.h"

#define	PORT	7777


int main(int argc, char*argv[]) {
	struct sockaddr_in server_addr, client_addr;
	int sd_server, *sd_client;

	thread_pool_t *tp;

	tp = (thread_pool_t *)malloc(sizeof(thread_pool_t));
	pool_init(tp, 8);


	if(( (sd_server) = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			printf("Errore nella creazione del server\n");
			exit(EXIT_FAILURE);
	}


	server_addr.sin_family = AF_INET; /* la famiglia dei protocolli */
	server_addr.sin_port = htons(PORT); /* la porta in ascolto */
	server_addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(sd_server, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
			printf("Errore di binding alla porta %d (%s)\n", PORT, strerror(errno));
			exit(EXIT_FAILURE);
	}

	if(listen(sd_server, 20) < 0) {
		printf("Errore in listening sulla porta: %d (%s)\n", PORT, strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("[+]In listening sulla porta %d \n", PORT);


	while(1) {
		sd_client = (int *) malloc (sizeof(int));
		size_t address_size = sizeof(client_addr);

		if((*sd_client = accept(sd_server, (&client_addr), &address_size)) < 0)
				printf("Errore nella chiamata accept\n");

		add_task(tp, menage_conn, (void *)sd_client);


	}



	close(sd_server);





		return EXIT_SUCCESS;
}




