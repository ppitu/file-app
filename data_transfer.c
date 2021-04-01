#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <arpa/inet.h>

#include "data_transfer.h"
#include "global_define.h"

void
recv_file	(int		sockfd,
		FILE		*fp)
{
	int		n;
	char		buffer[BUFFER_SIZE];

	while(1)
	{
		n = recv(sockfd, buffer, BUFFER_SIZE, 0);
		printf("[Recv - %d]%s", n, buffer);
		
		fprintf(fp, "%s", buffer);
		bzero(buffer, BUFFER_SIZE);

		if(n <= 0)
			break;

	}
}

void
send_file	(int		sockfd,
		FILE		*fp)
{
	int		n;
	char		buffer[BUFFER_SIZE] = {0};

	while(fgets(buffer, BUFFER_SIZE, fp) != NULL)
	{
		if(send(sockfd, buffer, sizeof(buffer), 0) == -1)
		{
			perror("[-]Error in sending file.\n");
			exit(1);
		}

		printf("[Sending]%s", buffer);
		bzero(buffer, BUFFER_SIZE);
	}
}

void
send_data	(int		sockfd,
		const char	*data)
{
	char		buffer[BUFFER_SIZE] = {0};

	strcpy(buffer, data);

	if(send(sockfd, buffer, BUFFER_SIZE, 0) == -1)
	{
		perror("[-]Error in sending\n");
		exit(1);
	}
}

void
recv_data	(int		sockfd,
		char		**result_data)
{
	char		buffer[BUFFER_SIZE] = {0};

	*result_data = malloc(BUFFER_SIZE * sizeof(char));

	if(recv(sockfd, buffer, BUFFER_SIZE, MSG_DONTWAIT) == -1)
	{
		perror("[-]Error in recv data\n");
		exit(1);
	}

	strcpy(*result_data, buffer);
}
