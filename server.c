#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>

#include "path.h"

#define SIZE 1024

void send_confirm(int sockfd)
{
	int			n;
	char 			buffer[SIZE];

	strcpy(buffer, "Yes");

	if(send(sockfd, buffer, SIZE, 0) == -1)
	{
		perror("[-]Error in send conf\n");
		exit(1);
	}
}

void recv_dir(int sockfd)
{
	int			n;
	char 			buffer[SIZE] = {0};

	while(1)
	{
		printf("Przed otrzymaniem danych\n");
		n = recv(sockfd, buffer, SIZE, 0);
		printf("Wyslalem %d\n", n);
		if(n <= 0)
			break;
	}

	printf("DIR: %s\n", buffer);
	bzero(buffer, SIZE);
}

void write_file(int sockfd)
{
	int			n;
	FILE			*fp;
	char			*filename = "revc.txt";
	char			buffer[SIZE];

	fp = fopen(filename, "w");

	printf("Zaczynam dzialanie\n");

	while(1)
	{
		n = recv(sockfd, buffer, SIZE, 0);

		if(n <= 0)
			break;
	}

	printf("%s\n", buffer);

	//fprintf(fp, "%s", buffer);
	bzero(buffer, SIZE);
}

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
	recv_dir(new_sock);
	printf("Wysylam potwierdzenie\n");
	send_confirm(new_sock);
	printf("Otrzymuje plik\n");
	write_file(new_sock);
	printf("[+]Data written in the file successfully\n");

	return 0;
}	
