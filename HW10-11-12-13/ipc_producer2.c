#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "shm_com.h"

int main()
{
	int shmid;
	void *shared_memory = (void *)0;
	pid_t pid;

	struct shared_use_st *shared_stuff;
	char buffer[BUFSIZ];

	char input[10];
	while(1){
		scanf("%s", input);
		if(!strcmp("start", input))
			break;
		else
			printf("Please input <start>\n");
	}

	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);

	if(shmid == -1){
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

	shared_memory = shmat(shmid ,(void *)0, 0);

	if(shared_memory == (void *)-1){
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}


	shared_stuff = (struct shared_use_st *)shared_memory;
	shared_stuff->student_num = 2014136082;
	shared_stuff->client_pid = getpid();
	shared_stuff->running = 2;
	
	pid = fork();
	if(pid == -1){
		printf("fork failed\n");
		exit(1);
	}
	else if(pid == 0)
		execl("./ipc_consumer2", "ipc_consumer2", NULL);  


	while(1){
		if(shared_stuff->running == 0)	break;
		else	sleep(1);
	}

	printf("Waiting....\n");
	
	printf("This is Producer.\n");
	printf("Producer PID : %d\n", getpid());
	printf("Consumer PID : %d\n", shared_stuff->client_pid);
	printf("Student Number : %d\n", shared_stuff->student_num);
	printf("Student Name : %s\n", shared_stuff->name);

	if(shmdt(shared_memory) == -1){
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	if(shmctl(shmid, IPC_RMID, 0) == -1){
		fprintf(stderr, "shmctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);

}
