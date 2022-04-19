/********************************************************************************************
*					FILENAME:c
**********************************************************************************************/
/* Title: 
 * Brief: 
 * Author: Sayali Mule
 * Date Created: April 9, 2022
 * Course: Advanced Embedded Software Development


 * Reference[1]: 
 * 
 * 
 * */
/****************************************************************************************
*					HEADER FILE SECTION
*****************************************************************************************/
#include "temperature_sensor.h"
#include "lux_sensor.h"
#include <stdio.h>
#include <stddef.h>
#include "timer.h"
#include "synchronization.h"
#include "server.h"
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "temperature_sensor.h"
#include "lux_sensor.h"
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

void* temperature_sensor_thread()
{
    bool status = 0;
    log_msg_t msg_packet = {0};

    while(1)
    {
        if(temp_sensor_time_expire == 1)
        {
            
            msg_packet.id = TEMPERATURE_SENSOR;
            msg_packet.time = get_time();
            status = read_temperature_value(&msg_packet.sensor_val ,TEMP_CELSIUS);
            if(status)
            {
                printf("\n\rread_temperature_value() returned 1");
            }
            pthread_mutex_lock(&msg_queue_mutex);
            if(mq_send(msg_queue_logger,(char*)&msg_packet, sizeof(log_msg_t),0) == -1)
            {
                printf("mq_send() failed in temperature thread");
            }
            pthread_mutex_unlock(&msg_queue_mutex);

            // printf("\n\r[%lf]Temperature value: %lf",msg_packet.time, msg_packet.sensor_val);
            temp_sensor_time_expire = 0;
        }
    }
}


void* light_sensor_thread()
{
    bool status = 0;
    double light_value = 0.0;
    double current_time = 0.0;
    thread_id_e thread_id = -1;
    log_msg_t msg_packet = {0};
    while(1)
    {
        if(light_sensor_time_expire == 1)
        {
            msg_packet.time = get_time();
            status  = read_light_value(&msg_packet.sensor_val);
            msg_packet.id = LIGHT_SENSOR;

            if(status)
            {
                printf("\n\rread_light_value() returned 1");
            }

            pthread_mutex_lock(&msg_queue_mutex);
            if(mq_send(msg_queue_logger,(char*)&msg_packet, sizeof(log_msg_t),0) == -1)
            {
                printf("\n\rmq_send() failed in light sensor thread");
            }
            pthread_mutex_unlock(&msg_queue_mutex);

            // printf("\n\r[%lf]light value: %lf",msg_packet.time,msg_packet.sensor_val);
            light_sensor_time_expire = 0;
        }
    }
}


void* log_thread(void* arg)
{
    log_msg_t recv_msg_packet = {0};
    while(1)
    {
        if(mq_receive(msg_queue_logger, (char*)&recv_msg_packet, sizeof(log_msg_t), NULL) == -1)
        {
            printf("\n\rmq_receive failed");
        }

        
        log_file = fopen(arg,"a+");
        if(recv_msg_packet.id == TEMPERATURE_SENSOR)
        {
            // printf("\n\r[%lf][%d] Temperature: %lf celsius",recv_msg_packet.time,recv_msg_packet.id, recv_msg_packet.sensor_val);
            fprintf(log_file,"\n\r[%lf][%d] Temperature: %lf celsius",recv_msg_packet.time,recv_msg_packet.id, recv_msg_packet.sensor_val);
        }
        else if(recv_msg_packet.id == LIGHT_SENSOR)
        {
            // printf("\n\r[%lf][%d] Light value: %lf ",recv_msg_packet.time,recv_msg_packet.id, recv_msg_packet.sensor_val);
            fprintf(log_file,"\n\r[%lf][%d] Light value: %lf ",recv_msg_packet.time,recv_msg_packet.id, recv_msg_packet.sensor_val);
        }
        fclose(log_file);

        
    }

}

void* server_thread()
{
	char buff[MAX];
	int n;
	// infinite loop for chat
	while(1) 
    {
		bzero(buff, MAX);

		// read the message from client and copy it in buffer
		read(connfd, buff, sizeof(buff));
        printf("%s %ld\n",buff,strlen(buff));
		// print buffer which contains the client contents
		// printf("From client: %s\t To client : ", buff);
        if(strcmp("Temp\n",buff) == 0)
        {
            printf("\n\rInside temperature");
          double temperature = 0.0;
          read_temperature_value(&temperature, TEMP_CELSIUS);

          write(connfd,&temperature,sizeof(double));  
        }
        else if(strcmp("Light\n",buff) == 0)
        {
            printf("\n\rInside light");
            double light_val = 0.0;
            read_light_value(&light_val);
            write(connfd,&light_val,sizeof(double));
        }

		// copy server message in the buffer



		// if msg contains "Exit" then server exit and chat ended.
		if (strncmp("exit", buff, 4) == 0) 
        {
            close(sockfd);
			printf("Server Exit...\n");
			break;
		}

        bzero(buff, MAX);

	}
} 