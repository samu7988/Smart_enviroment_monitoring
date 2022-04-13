#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    printf("Hi I am client");
    struct sockaddr_in server_address;

    //creating a socket
    int client_fd = socket(AF_INET, SOCK_STREAM,0);

    if(client_fd < 0)
    {
        printf("\n\rsocket() failed");
        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6666);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    int client_status = 0;
    client_status = connect(client_fd,(struct sockaddr *)&server_address, sizeof(server_address) < 0 );

    if(client_status < 0)
    {
        printf("\n\rConnection failed to establish with server(beaglebone black)");
        close(client_fd);
        return -1;
    }

    while(1)
    {
        printf("\n\rClient connection looks to be established");
    }
}