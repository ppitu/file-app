#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ioctl.h>
#include <arpa/inet.h>

#include "path.h"
#include "data_transfer.h"

#define SIZE 1024


int main()
{
	char			*ip = "127.0.0.1";
	int			port = 8080;
	int			e;

	int			sockfd, new_sock;
	struct 			sockaddr_in server_addr, new_addr;
	socklen_t		addr_size;
	char			buffer[SIZE];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0)
	{
		perror("[-]Error in socket");
		exit(1);
	}

	printf("[+]Server socket create successfully.\n");

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	server_addr.sin_addr.s_addr = inet_addr(ip);

	e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

	if(e < 0)
	{
		perror("[-]Error in bind");
		exit(1);
	}

	printf("[+]Bind successful.\n");

	if(listen(sockfd, 10) == 0)
	{
		printf("[+}Listening....\n");
	} else {
		perror("[-]Error in listening\n");
		exit(1);
	}

	addr_size - sizeof(new_addr);
	new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
	
	FILE *fp = fopen("recv.txt", "w");

	
	char *data;
	recv_data(new_sock, &data);
	printf("%s\n", data);

	send_data(new_sock, "Odebralem");

	printf("==========================\n");
	recv_file(new_sock, fp);

	free(data);
	fclose(fp);
	printf("[+]Data written in the file successfully\n");

	return 0;
}	
