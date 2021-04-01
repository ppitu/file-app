all:
	gcc -o server server.c data_transfer.c
	gcc -o client client.c data_transfer.c
