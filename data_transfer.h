#ifndef DATA_TRANSFER_H
#define DATA_TRANSFER_H

void
recv_file	(int		sockfd,
		FILE		*fp);

void
send_file	(int		sockfd,
		FILE		*fp);

void
send_data	(int		sockfd,
		const char	*data);

void 
recv_data	(int		sockfd,
		char		**result_data);

#endif //DATA_TRANSFER_H
