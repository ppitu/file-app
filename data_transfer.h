#ifndef DATA_TRANSFER_H
#define DATA_TRANSFER_H

void 
send_data      	(int 		sockfd, 
		const char	*data);

void 
recv_data	(int 		sockfd, 
		char		*data);

#endif //DATA_TRANSFER_H
