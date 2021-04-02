#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <arpa/inet.h>

#include "data_transfer.h"
#include "global_define.h"

void
recv_file	(int		sockfd,
		FILE		*fp)
{
	int			n;
	char			buffer[BUFFER_SIZE] = {0};

	while(1)
	{
		n = recv_int(sockfd);

		if(n <= 0)
			break;

		bzero(buffer, BUFFER_SIZE);
		n = recv(sockfd, buffer, BUFFER_SIZE, 0);

		fprintf(fp, "%s", buffer);

		if(n <= 0)
			break;
	}

	bzero(buffer, BUFFER_SIZE);
}

void
send_file	(int		sockfd,
		FILE		*fp)
{
	int			n;
	char			buffer[BUFFER_SIZE] = {0};

	while(fgets(buffer, BUFFER_SIZE, fp) != NULL)
	{
		send_int(sockfd, BUFFER_SIZE);

		if(send(sockfd, buffer, sizeof(buffer), 0) == -1)
		{
			perror("[-]Error in sending file.\n");
			exit(1);
		}

		bzero(buffer, BUFFER_SIZE);
	}

	send_int(sockfd, 0);
}

void
send_data	(int		sockfd,
		const char	*data)
{
	char		buffer[BUFFER_SIZE] = {0};

	strcpy(buffer, data);

	send_int(sockfd, BUFFER_SIZE);

	if(send(sockfd, buffer, BUFFER_SIZE, 0) == -1)
	{
		perror("[-]Error in sending\n");
		exit(1);
	}

	send_int(sockfd, 0);
}

void
recv_data	(int		sockfd,
		char		**result_data)
{
	char			buffer[BUFFER_SIZE] = {0};
	int 			n;
	int			number_of_data = 1;

	*result_data = malloc(1 * sizeof(char));

	while(1)
	{

		n = recv_int(sockfd);

		if(n <= 0)
		{
			break;
		}

		bzero(buffer, BUFFER_SIZE);
				
		n = recv(sockfd, buffer, BUFFER_SIZE, 0);

		if(n < 0)
		{
			perror("[-]Error in recv data\n");
			exit(1);

		}

		*result_data = realloc(*result_data, BUFFER_SIZE * number_of_data);

		strcpy(*result_data, buffer);

		number_of_data++;
	}
}

void
send_int	(int		sockfd,
		int		number_to_send)
{
	int			converted_number;

	converted_number = htonl(number_to_send);

	send(sockfd, &converted_number, sizeof(converted_number), 0);
}

int
recv_int	(int		sockfd)
{
	int 			result;
	int			n;

	n = recv(sockfd, &result, sizeof(result), 0);

	if(n > 0)
		return ntohl(result);
	else
		return -1;
}
