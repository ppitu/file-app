#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <arpa/inet.h>

#include "data_transfer.h"

#define SIZE 1024


int main()
{
	char			*ip = "127.0.0.1";
	int			port = 8080;
	int			e;

	int			sockfd;
	struct 			sockaddr_in server_addr;
	FILE			*fp;
	char			*filename = "send.txt";

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0)
	{
		perror("[-]Error in socket\n");
		exit(1);
	}

	printf("[+]Server socket created successfully\n");

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	server_addr.sin_addr.s_addr = inet_addr(ip);

	e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

	if(e == -1)
	{
		perror("[-]Error in socket\n");
		exit(1);
	}

	printf("[+]Connected to socket\n");

	fp = fopen(filename, "r");

	if(fp == NULL)
	{
		perror("[-]Error in reading file\n");
		exit(1);
	}

	char *data;

	send_data(sockfd, "Hello Peter");
	printf("Send data\n");
	recv_data(sockfd, &data);
	printf("Recv data\n");
	printf("%s\n", data);
	free(data);
	send_file(sockfd, fp);
	printf("[+]File data send successfully\n");

	printf("[+]Closing the connection\n");

	fclose(fp);

	close(sockfd);

	return 0;
}
