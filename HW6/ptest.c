#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void main() {
	struct tm *t_info;
	time_t t;

	while(1) {
		time(&t);
		t_info = localtime(&t);
		
		printf("localtime : %s", asctime(t_info));
		sleep(2);
	}
}
