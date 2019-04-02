#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS     2

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int count_global = 0;

void *perform_work(void *argument)
{
	int i;
	for (i = 0; i < 50000; i++)
	{
		pthread_mutex_lock(&m);
		*(int*)argument = *(int*)argument + 1;
		count_global++;
		pthread_mutex_unlock(&m);
	}
	return NULL;
}

//void *perform_work1(void *argument)
void *perform_work1()
{
	int i;
	for(i = 0; i < 10000; i++)
	{
		pthread_mutex_lock(&m);
		//*(int*)argument = *(int*)argument + 1;
		count_global++;
		pthread_mutex_unlock(&m);
	}
	return NULL;
}

void *perform_work2()
{
	int i;
	for (i = 0; i < 10000; i++)
	{
		pthread_mutex_lock(&m);
		//*(int*)argument = *(int*)argument + 1;
		count_global++;
		pthread_mutex_unlock(&m);
	}
	return NULL;
}

int main(void)
{
	pthread_t threads[NUM_THREADS];
	int result_code, index;
	int count_local = 0;
	//int result_code1, result_code2;

	// create all threads one by one
	for (index = 0; index < NUM_THREADS; ++index) {
		printf("In main: creating thread %d\n", index);
		result_code = pthread_create(&threads[index], NULL, perform_work, &count_local);
	}

/*	result_code1 = pthread_create(&threads[0], NULL, perform_work1, NULL);
	result_code2 = pthread_create(&threads[1], NULL, perform_work2, NULL);*/

	// wait for each thread to complete
	for (index = 0; index < NUM_THREADS; ++index) {
		// block until thread 'index' completes
		result_code = pthread_join(threads[index], NULL);
		printf("In main: thread %d has completed\n", index);
	}

	/*result_code1 = pthread_join(threads[0], NULL);
	result_code2 = pthread_join(threads[1], NULL);*/

	printf("count_local = %d\n",count_local);
	printf("count_global = %d\n", count_global);
	printf("In main: All threads completed successfully\n");
	exit(EXIT_SUCCESS);
}