// Test the pid manager using threads.

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "pidmanager.h"

#define NUM_THREADS 100
void *getPid(void * time);
void createThreads(pthread_t workers[], pthread_attr_t attr);
void waitForThreadsToFinish(pthread_t workers[]);

int main(int argc, char *argv[])
{
	srand(time(NULL));
	pthread_attr_t attr;
	pthread_t workers[NUM_THREADS];
	
	pthread_attr_init(&attr);
	if(!allocate_map())
	{
		return 1;
	}

	createThreads(workers, attr);
	waitForThreadsToFinish(workers);
	
	printf("Finished.\n");
	return 0; 
}

void createThreads(pthread_t workers[], pthread_attr_t attr)
{
	int i;
	int time;
	for(i = 0; i < NUM_THREADS; i++)
	{
		time = rand() % 10 + 1;
		printf("Thread %d of %d: ", i+1, NUM_THREADS);
		pthread_create(&workers[i], &attr, getPid, &time);
		sleep(time/4); //short pause before creating next thread
	}
}

void * getPid(void * time)
{
	int * ints = (int *)time;
	int sleepTime = *ints;
	int pid = allocate_pid();
	printf("pid %d. Sleeping for %d seconds.\n", pid, sleepTime);
	sleep(sleepTime);
	printf("Releasing pid %d.\n", pid);
	release_pid(pid);
	pthread_exit(0);
}

void waitForThreadsToFinish(pthread_t workers[])
{
	int i;
	for(i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(workers[i], NULL);
	}
}
