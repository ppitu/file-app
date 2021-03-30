#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <arpa/inet.h>

#define SIZE 1024

void recv_confirm(int sockfd)
{
	int  			n;
	char 			buffer[SIZE];

	while(1)
	{
		n = recv(sockfd, buffer, SIZE, MSG_DONTWAIT);

		if(n <= 0)
			break;
	}

	printf("%s\n", buffer);
	bzero(buffer, SIZE);
}

void send_dir(int sockfd)
{
	int 			n;
	char			*napis = "Test123/Test1/Test23/send.txt";
	char 			buffer[SIZE];

	strcpy(buffer, napis);

	printf("%s\n", buffer);

	if(send(sockfd, buffer, SIZE, 0) == -1)
	{
		perror("[-] Error in sending file.\n");
		exit(1);
	}
	printf("Wyslalem sciezke\n");
	bzero(buffer, SIZE);
}

void send_file(FILE *fp, int sockfd)
{
	int 			n;
	char 			data[SIZE] = {0};

	while(fgets(data, SIZE, fp) != NULL)
	{
		if(send(sockfd, data, sizeof(data), 0) == -1)
		{
			perror("[-]Error in sending file.");
			exit(1);
		}

		bzero(data, SIZE);
	}
}

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

	send_dir(sockfd);
	recv_confirm(sockfd);
	send_file(fp, sockfd);

	printf("[+]File data send successfully\n");

	printf("[+]Closing the connection\n");

	close(sockfd);

	return 0;
}
