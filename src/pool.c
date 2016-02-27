/*
 ============================================================================
 Name        : pool.h
 Author      : Luca Maria Castiglione
 Version     : 0.1
 Copyright   : This file is part of FraWs released under GNU/GPL v 2 license
 Description : FraWs 0.1
 ============================================================================
 */


#include "headers/pool.h"


static void pool_remove(thread_pool_t * tp);


int pool_init(thread_pool_t * tp, const int n)
{
	int i;

	pthread_attr_init(&(tp->a));
	pthread_attr_setdetachstate(&(tp->a), PTHREAD_CREATE_JOINABLE);

	tp->threads = (pthread_t *) malloc(n * sizeof(pthread_t));

	if(tp->threads == NULL) {
		printf("Fatal error (%s)\n", strerror(errno));
		return -1;
	}

	tp->nt = n;
	tp->left = 0;
	tp->remove = 0;

	pthread_mutex_init(&(tp->mutex), 0);
	pthread_cond_init(&(tp->empty), 0);

	tp->tail = NULL;
	tp->head = NULL;

	printf("[+]Thread pool is up %d threads created!\n", n);

	for(i = 0; i < n; i++)
		pthread_create(&(tp->threads)[i], &(tp->a), job, tp);



	return 1;

}


int	add_task(thread_pool_t * tp, void *(*f)(void *), void *arguments)
{
	job_t *tmp;

	tmp = (job_t *)malloc(sizeof(job_t));

	tmp->f = f;
	tmp->value = arguments;
	tmp->next = NULL;

	pthread_mutex_lock(&(tp->mutex));

	if(tp->tail != NULL)
		tp->tail->next = tmp;

	tp->tail = tmp;

	if(tp->head == NULL)
		tp->head = tp->tail;

	(tp->left)++;

	//printf("task added\n");
	pthread_cond_signal(&(tp->empty));
	pthread_mutex_unlock(&(tp->mutex));

	return 1;
}

void pool_close(thread_pool_t *tp)
{
	int i;

	pthread_mutex_lock(&(tp->mutex));
	tp->remove = 1;
	pthread_cond_broadcast(&(tp->empty));
	pthread_mutex_unlock(&(tp->mutex));

	for(i = 0; i < tp->nt; i++)
		pthread_join(tp->threads[i], 0);


	pool_remove(tp);
}

static void pool_remove(thread_pool_t * tp)
{


	pthread_mutex_destroy(&(tp->mutex));
	pthread_cond_destroy(&(tp->empty));
	free(tp->threads);

}

void *job(void *d)
{
	thread_pool_t *tp;
	job_t *tmp;


	tp = (thread_pool_t *)(d);

	while(tp->remove == 0 ) {
		pthread_mutex_lock(&(tp->mutex));

		while(tp->remove == 0 && tp->head == NULL)
			pthread_cond_wait(&(tp->empty), &(tp->mutex));

		if(tp->remove != 0) {
			 pthread_mutex_unlock(&(tp->mutex));
			 pthread_exit(0);
		}


		tmp = tp->head;
		tp->head = tmp->next;

		if(tmp == tp->tail)
			tp->tail = NULL;

		(tp->left)--;
		pthread_mutex_unlock(&(tp->mutex));


		tmp->f( (tmp->value) );
		free(tmp);




	}

	pthread_exit(0);
}
