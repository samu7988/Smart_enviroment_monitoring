#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MAX 80
#define PORT 7000
#define SA struct sockaddr


/***********************************************************************************************
 * @brief func() is for communication with server or msg passing to the server 
 * 
 *
 *
 * @param : 
 *
 * @return : none
 *********************************************************************************************/



void func(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("\n\rEnter 1.Temp in celsius \n \
                          2.Light \n \
                          3.Temp in Kelvin \n  \
                          4.Temp in Fahrenheit \n  ");

        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        buff[n] = '\0';
        write(sockfd, buff, sizeof(buff));
        double val;
        read(sockfd, &val, sizeof(double));
        if(strcmp(buff, "1\n") == 0)
        {
            printf("\n\rFrom Server : %lf celsius", val);
        }
        else if(strcmp(buff, "2\n") == 0)
        {
            printf("\n\rServer: %lf lumen", val);
        }
        else if(strcmp(buff, "3\n") == 0)
        {
            printf("\n\rFrom Server: %lf kelvin",val);
        }
        else if(strcmp(buff, "4\n") == 0)
        {
            printf("\n\rServer: %lf fahrenheit",val);
        }
        else if ((strcmp(buff, "5\n")) == 0) {
            printf("Client Exit...\n");
            break;
        }
        else 
        {
            printf("\n\rServer: %lf",val);
        }

    }
}
   


/***********************************************************************************************
 * @brief : client socket creating 
 *          assigning IP to the PORT
 *          
 *
 * 
 *
 *
 * @param address:
 *
 * @return 
 *********************************************************************************************/



int main()
{
    int sockfd;
    struct sockaddr_in servaddr;
   
    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("10.0.0.68");
    servaddr.sin_port = htons(PORT);
   
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        perror("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
   
    // function for chat
    func(sockfd);
   
    // close the socket
    close(sockfd);
}