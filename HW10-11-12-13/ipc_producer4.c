#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "socket_path"
#define BUFF_SIZE 1024

struct my_msg_st{
	int p_pid;
	int c_pid;
	int student_num;
	char name[BUFSIZ];
};

int main()
{
	int producer_socket;
	int consumer_socket;
	int consumer_size;
	pid_t pid;

	struct sockaddr_un producer_addr;
	struct sockaddr_un consumer_addr;
	struct my_msg_st some_data;

	char buff_snd[BUFF_SIZE];

	char p_pid[20];
	char c_pid[20];
	char name[20] = {0};
	char student_num[11] = {0};
	
	char input[10] = {0};
	while(1){
		scanf("%s", input);
		if(!strcmp("start", input))
			break;
		else
			printf("Please input <start>\n");
	}

	unlink(SOCK_PATH);
	producer_socket = socket(AF_UNIX, SOCK_STREAM, 0);
	if(producer_socket == -1){
		fprintf(stderr, "Failed to create producer socket\n");
      		exit(EXIT_FAILURE);
	}
	memset(&producer_addr, 0, sizeof(producer_addr));
	producer_addr.sun_family= AF_UNIX;

	strcpy(producer_addr.sun_path,SOCK_PATH);

	if(bind(producer_socket, (struct sockaddr*)&producer_addr, 
					sizeof(producer_addr)) == -1){
		fprintf(stderr, "bind() execution error\n");
		exit(EXIT_FAILURE);
	}

	if(listen(producer_socket, 5) == -1){
		fprintf(stderr,  "listen() execution fail\n");
		exit(EXIT_FAILURE);
   	}

	pid = fork();
	if(pid == -1){
		printf("fork failed\n");
		exit(1);
	}
	else if(pid == 0)
		execl("./ipc_consumer4", "ipc_consumer4", NULL);  


	some_data.student_num = 2014136082;
	some_data.p_pid = getpid();

	
	consumer_size = sizeof(consumer_addr);
	consumer_socket = accept(producer_socket,
		(struct sockaddr*)&consumer_addr, &consumer_size);
		
	if (consumer_socket == -1){
		fprintf(stderr, "Failed to connect\n");
		exit(EXIT_FAILURE);
	}

	write(consumer_socket,&some_data,sizeof(some_data));
	read(consumer_socket,&some_data,sizeof(some_data));
	
	printf("This is Producer.\n");
	printf("Producer PID : %d\n", some_data.p_pid);
	printf("Consumer PID : %d\n", some_data.c_pid); 
	printf("Student Number : %d\n", some_data.student_num);
	printf("Student Name : %s\n", some_data.name);

	close(consumer_socket);
	exit(EXIT_SUCCESS);
}
