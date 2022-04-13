#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    printf("Hi I am client");
    struct sockaddr_in client_address;

    //creating a socket
    int client_fd = socket(AF_INET, SOCK_STREAM,0);

    if(client_fd < 0)
    {
        printf("\n\rsocket() failed");
        return -1;
    }

    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(7000);
    client_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    int client_status = 0;
    client_status = connect(client_fd,(struct sockaddr *)&client_address, sizeof(client_address) < 0 );

    if(client_status < 0)
    {
        perror("\n\rConnection failed to establish with server(beaglebone black)");
        close(client_fd);
        return -1;
    }

    printf("\n\r connection successfull");
    char recv_msg[255];
    recv(client_fd,recv_msg,sizeof(recv_msg),0);
    printf("message received:%s",recv_msg);
    
    while(1)
    {
        printf("\n\rClient connection looks to be established");
    }
}