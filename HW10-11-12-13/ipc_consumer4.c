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

int   main()
{
	int consumer_socket;	
	pid_t pid;

	struct sockaddr_un consumer_addr;
	struct my_msg_st some_data;

	char buff_snd[BUFF_SIZE];

	consumer_socket = socket(AF_UNIX, SOCK_STREAM, 0);
	if(consumer_socket == -1){
		fprintf(stderr, "Failed to create producer socket\n");
      		exit(EXIT_FAILURE);
	}

	memset(&consumer_addr, 0, sizeof(consumer_addr));
	consumer_addr.sun_family = AF_UNIX;
	strcpy(consumer_addr.sun_path, SOCK_PATH);

	if(connect(consumer_socket,(struct sockaddr*)&consumer_addr, 
						sizeof(consumer_addr)) == -1)
	{
		fprintf(stderr, "Failed to connect\n");
      		exit(EXIT_FAILURE);
	}

	read(consumer_socket,&some_data,sizeof(some_data));

	printf("This is Consumer\n");
	printf("Producer PID : %d\n", some_data.p_pid);

	some_data.c_pid = getpid();
	strcpy(some_data.name, "Oh seungeun");
	write(consumer_socket,&some_data,sizeof(some_data));

	close(consumer_socket);
	return 0;
}
