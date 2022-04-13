/********************************************************************************************
*					FILENAME:c
**********************************************************************************************/
/* Title: 
 * Brief: 
 * Author: Sayali Mule
 * Date Created: April 12, 2022
 * Course: Advanced Embedded Software Development
 

 * Reference[1]: 
 * 
 * 
 * */
/****************************************************************************************
*					HEADER FILE SECTION
*****************************************************************************************/
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
/**************************************************************************************
*					GLOBAL VARIABLE
*******************************************************************************************/

/**********************************************************************************
*				FUNCTION DEFINITION
***************************************************************************************/
/***********************************************************************************************
 * @brief 
 *
 *
 *
 * @param address:
 *
 * @return 
 *********************************************************************************************/
bool server_init()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0)
    {
        printf("\n\rsocket() server failed");
        return 1;
    }
    struct sockaddr_in  server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(6666);

    int server_status = bind(server_fd, (struct sockaddr*)&server_address, sizeof(server_address));
    if(server_status)
    {
        printf("\n\rbind() failed");
        return 1;
    }

    int num_client = 3;
    server_status = listen(server_fd, num_client);
    if(server_status == -1)
    {
        printf("\n\rlisten() failed");
        return 1;
    }

    server_status = accept(server_fd, (struct sockaddr*)0, 0);
    if(server_status == -1)
    {
        printf("\n\raccept() failed");
        return 1;
    }

    while(1)
    {
        printf("\n\rserver is connected");
    }

}

