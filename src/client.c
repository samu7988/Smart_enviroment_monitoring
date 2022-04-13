#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SA struct sockaddr
int main()
{
    int clientfd;
	struct sockaddr_in client_addr;

	// socket create and verification
	clientfd = socket(AF_INET, SOCK_STREAM, 0);
	if (clientfd == -1) 
    {
		printf("\n\rsocket() failed");
	}

	bzero(&client_addr, sizeof(client_addr));

	// assign IP, PORT
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	client_addr.sin_port = htons(7000);

	// connect the client socket to server socket
	if (connect(clientfd, (struct sockaddr*)&client_addr, sizeof(client_addr)) != 0) 
    {
		printf("connection with the server failed...\n");
	}

    char recv_msg[255];
    printf("message received:%s",recv_msg);

    while(1)
    {
        printf("\n\rClient connection looks to be established");
    }
}