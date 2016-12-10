#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#define TOTALTHREAD 10

void *threadFunction(void *arg);

void initCompleteCount();
int compareThreadCount(int cnt); 
int minimumCount();

sem_t bin_sem
int thCount[TOTALTHREAD];
int main() {
	int res = 0;
	pthread_t a_thread[TOTALTHREAD]; 
	int *threadResult;	

	printf("2014136082 Oh seungeun\n");

	res = sem_init(&bin_sem, 0, 0);
	if (res != 0) { 
		printf("Semaphore Error!!\n");
	 	return -1;
	} 
	

	for ( int i = 0 ; i < TOTALTHREAD ; i++ ) {	
		res = pthread_create(&(a_thread[i]), NULL, &threadFunction, (void *)i);
		printf("Create %d thread\n", i);
		if (res != 0) {
			printf("Thread Creation Failed\n");
			return -1;
		} 
	}
	
	sleep(3);
	sem_post(&bin_sem);

	for ( int i = TOTALTHREAD - 1 ; i >= 0 ; i-- ) {
		res = pthread_join(a_thread[i], (void **)&threadResult);
		printf("Exit %d thread\n", i);
		if (res != 0) {
			printf("Thread Join Failed\n");
			return -1;
		}
	}
	printf("Finished (Thread)\n");

	return 0;
}

void *threadFunction(void *arg) {
	int count = 0, complete = 0;
	int r = 0;
	int running = 0;
	int num =(int *)arg; 
	time_t locTime;
	struct tm *t; 

	initCompleteCount();
	sem_wait(&bin_sem); 
	while ( 1 ) {
		if ( count == 20 ) { 
			printf("Thread Exit\n");
			break;
		} 

		if ( count == minimumCount() && complete == 0 ) { 
			long seed = rand()%1000 + 1;
			srand(seed);
			r = rand() % 10;	
	
			locTime = time(NULL);
			t = localtime(&locTime);


			printf("num :: %2d, count :: %d, ", num+1, count);
			printf("localTime :: %4d.%2d.%2d. %2d:%2d:%2d\n", t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

			thCount[num]++;
			sem_post(&bin_sem); 
			complete = 1; 
			sleep(r);
		}
		else {
			sem_post(&bin_sem); 
			sleep(1);
			
		}

		if ( compareThreadCount(count) ) { 
			sem_wait(&bin_sem);
			count++;
			complete = 0; 
			sleep(1);
		}
	} 
	pthread_exit(NULL);
}

void initCompleteCount() {
	int i;
	for ( i = 0 ; i < TOTALTHREAD; i++ )
		thCount[i] = 0;
}

int compareThreadCount(int cnt) {

	int i, check = 0;
	for ( i = 0 ; i < TOTALTHREAD ; i++ ) {
		if ( thCount[i] == cnt )
			check++;
	}
	if ( check == 0 )
		return 1;
	else
		return 0;	
}

int minimumCount() {
	int i, min = 0;
	for ( i = 0 ; i < TOTALTHREAD ; i++ ) {
		if ( thCount[min] > thCount[i] )
			min = i;
	}
	return thCount[min];
}
