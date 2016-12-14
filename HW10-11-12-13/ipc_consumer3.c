#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msg_st{
	long int message_type;
	pid_t client_pid;
	int student_num;
	char name[BUFSIZ];
};

int main()
{
	int msgid_s, msgid_r;
	
	struct my_msg_st some_data;
	long int msg_to_receive = 0;

	msgid_s = msgget((key_t)1234, 0666 | IPC_CREAT);
	if(msgid_s == -1){
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	if(msgrcv(msgid_s, (void *)&some_data, BUFSIZ, msg_to_receive, 0) == -1){
		fprintf(stderr, "msgsnd failed\n");
		exit(EXIT_FAILURE);
	}

	printf("This is Consumer.\n");
	printf("Producer PID : %d\n", some_data.client_pid);


	msgid_r = msgget((key_t)1235, 0666 | IPC_CREAT);
	if(msgid_r == -1){
		fprintf(stderr, "msgget failed with error : %d\n", errno);
		exit(EXIT_FAILURE);
	}

	some_data.message_type = 1;
	strcpy(some_data.name, "Oh seungeun"); 
	some_data.client_pid = getpid();
		
	if(msgsnd(msgid_r, (void *)&some_data, BUFSIZ, 0) == -1){
		fprintf(stderr, "msgsnd error : %d", errno);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
