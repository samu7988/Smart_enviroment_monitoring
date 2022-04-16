/**
* Simple example for C project build
*/

#include <stdio.h>
#include "timer.h"
#include "i2c.h"
#include <stdint.h>
#include "temperature_sensor.h"
#include "lux_sensor.h"
#include "server.h"
#include <pthread.h>
#include "thread.h"
#define TEMP_SENSOR_ADDRESS (0x48)
#define THIGH_REG		(0x03)
int main(void)
{
	// uint8_t buffer[2] = {0xFE, 0x8A};
	// uint8_t receive_data[2] = {0};
	// i2c_write(TMP102_SENSOR_ADDRESS,THIGH_REG, buffer, 2);
	// i2c_read(TMP102_SENSOR_ADDRESS,THIGH_REG,receive_data,2);
	// for(int i = 0; i < 2; i++)
	// {
	// 	printf("\n\rReceive data: %u",receive_data[i]);
	// }

	enable_lightsensor();
	time_create();
	//server_init();
	pthread_t temperature_thread;
	pthread_t light_thread;
	pthread_t logger_thread;

	pthread_create(&temperature_thread, NULL, temperature_sensor_thread, NULL);
	pthread_create(&light_thread, NULL, light_sensor_thread, NULL);
	pthread_create(&logger_thread, NULL, log_thread, NULL);


	pthread_join(temperature_thread, NULL);
	pthread_join(light_thread, NULL);
	
	printf("Hello and welcome to ECEN5013!\n");
	while(1);
}

// #include <stdio.h>
// #include <netdb.h>
// #include <netinet/in.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <sys/types.h>
// #define MAX 80
// #define PORT 8080
// #define SA struct sockaddr

// // Function designed for chat between client and server.
// void func(int connfd)
// {
// 	char buff[MAX];
// 	int n;
// 	// infinite loop for chat
// 	for (;;) {
// 		bzero(buff, MAX);

// 		// read the message from client and copy it in buffer
// 		read(connfd, buff, sizeof(buff));
// 		// print buffer which contains the client contents
// 		printf("From client: %s\t To client : ", buff);
// 		bzero(buff, MAX);
// 		n = 0;
// 		// copy server message in the buffer
// 		while ((buff[n++] = getchar()) != '\n')
// 			;

// 		// and send that buffer to client
// 		write(connfd, buff, sizeof(buff));

// 		// if msg contains "Exit" then server exit and chat ended.
// 		if (strncmp("exit", buff, 4) == 0) {
// 			printf("Server Exit...\n");
// 			break;
// 		}
// 	}
// }

// // Driver function
// int main()
// {
// 	int sockfd, connfd, len;
// 	struct sockaddr_in servaddr, cli;

// 	// socket create and verification
// 	sockfd = socket(AF_INET, SOCK_STREAM, 0);
// 	if (sockfd == -1) {
// 		printf("socket creation failed...\n");
// 		exit(0);
// 	}
// 	else
// 		printf("Socket successfully created..\n");
// 	bzero(&servaddr, sizeof(servaddr));

// 	// assign IP, PORT
// 	servaddr.sin_family = AF_INET;
// 	servaddr.sin_addr.s_addr = inet_addr("10.0.0.68");
// 	servaddr.sin_port = htons(PORT);

// 	// Binding newly created socket to given IP and verification
// 	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
// 		printf("socket bind failed...\n");
// 		exit(0);
// 	}
// 	else
// 		printf("Socket successfully binded..\n");

// 	// Now server is ready to listen and verification
// 	if ((listen(sockfd, 5)) != 0) {
// 		printf("Listen failed...\n");
// 		exit(0);
// 	}
// 	else
// 		printf("Server listening..\n");
// 	len = sizeof(cli);

// 	// Accept the data packet from client and verification
// 	connfd = accept(sockfd, (SA*)&cli, &len);
// 	if (connfd < 0) {
// 		printf("server accept failed...\n");
// 		exit(0);
// 	}
// 	else
// 		printf("server accept the client...\n");

// 	// Function for chatting between client and server
// 	func(connfd);

// 	// After chatting close the socket
// 	close(sockfd);
// }
