#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define TOTALTHREAD 10

void *threadFunction(void *arg);
int main() {
	int res = 0;
	pthread_t a_thread[TOTALTHREAD]; 
	int *threadResult;	

	printf("2014136082 Oh seungeun\n");


	for ( int i = 0 ; i < TOTALTHREAD ; i++ ) {	
		res = pthread_create(&(a_thread[i]), NULL, &threadFunction, (void *)i);
		printf("Create %d thread\n", i);
		if (res != 0) {
			printf("Thread Creation Failed\n");
			return -1;
		}
	}
	
	sleep(3);

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
	int count = 0;
	int r = 0;
	int num =(int *)arg;
	time_t locTime;
	struct tm *t;

	while ( count++ <= 20 ) {
		if ( count == 20 ) {
			printf("Thread Exit\n");
			break;
		} 

		long seed = rand()%1000 + 1;
		srand(seed); 
		r = rand() % 10;	
	
	
		locTime = time(NULL);
		t = localtime(&locTime);

		sleep(r);
		printf("Thread No. :: %2d, count :: %d, ", num+1, count);
		printf("localTime :: %4d.%2d.%2d. %2d:%2d:%2d\n", t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	}
	pthread_exit(NULL);
}
