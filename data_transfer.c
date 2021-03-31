#include <string.h>


#include "data_transfer.h"
#include "global_define.h"

void
divide_string	(char		*str,
		char		**result_array,
		int		*array_size)
{
	int		str_size;
	int		i;
	int		size_of_last_portion;

	str_size = strlen(str);

	if((str_size % BUFFER_SIZE) == 0)
	{
		*array_size = str_size / BUFFER_SIZE;
	} else 
	{
		*array_size = str_size / BUFFER_SIZE + 1;
	}

	result_array = malloc(*array_size * sizeof(char *));

	size_of_last_portion = str_size % BUFFER_SIZE;

	for(i = 0; i < *array_size; i++)
	{
		*(result_array + i) = malloc(BUFFER_SIZE * sizeof(char));
		
		if((*array_size - 1) == i)
		{
			
		}
	}
}


void
send_data	(int		sockfd,
		const char	*data)
{
	
}

void
recv_data	(int		sockfd,
		char		*data)
{
	
}
