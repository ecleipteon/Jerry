/*
 ============================================================================
 Name        : pool.h
 Author      : Luca Maria Castiglione
 Version     : 0.1
 Copyright   : This file is part of FraWs released under GNU/GPL v 2 license
 Description : FraWs 0.1
 ============================================================================
 */


#ifndef FRAWS_SRC_HEADERS_POOL_H_
#define FRAWS_SRC_HEADERS_POOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

typedef struct job_t {

	void *value;		/* Argument to function f needs */
	void *(*f)(void *);	/* Pointer to function you want to put in queue */
	struct job_t *next;

}job_t;

typedef struct thread_pool_t {

	pthread_t *threads;

	pthread_mutex_t mutex;
	pthread_cond_t	empty;

	pthread_attr_t a;

	int left;
	int nt;

	struct job_t *head;
	struct job_t *tail;

	unsigned int remove; /* if high and no elements are in queue close the pool */

}thread_pool_t;

int 	pool_init(thread_pool_t * tp, const int n);
							/*
							 * This function will create a thread pool at the
							 * address tp point. The integer n will specify how
							 * many threads you want to create. It will return 1
							 * for success, -1 if an error occurred.
							 */

int	add_task(thread_pool_t * tp, void *(*f)(void *), void *arguments);
							/*
							 * This function will add a task (job_t) to scheduling
							 * queue. The function return 1.
							 * TODO: the function return -1 if an errorr occurred
							 */

void 	pool_close(thread_pool_t *tp);			/*
							 * This function will close the thread pool.
							 * It will wait for al job suspended in queue
							 * before the deallocation of all dynamic elements.
							 */

void 	*job(void *d);					/*
							 * Although it is not declared  as static, this
							 * function is supposed to be used exclusively by
							 * pool_init() as procedure for pthread_create().
							 * This is the function all threads use to
							 * execute jobs in queue.
							 */



#endif /* FRAWS_SRC_HEADERS_POOL_H_ */
