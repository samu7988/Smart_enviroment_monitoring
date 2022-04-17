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
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include "synchronization.h"
#include <stdlib.h>
#include <unistd.h>
/**************************************************************************************
*					GLOBAL VARIABLE
*******************************************************************************************/
#define MAX_MSG (9)
mqd_t msg_queue_logger ;
FILE* log_file = NULL;
pthread_mutex_t i2c_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t msg_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t log_file_mutex = PTHREAD_MUTEX_INITIALIZER;
int sockfd = 0; 
/**********************************************************************************
*				FUNCTION DEFINITION
***************************************************************************************/
void terminate_signal_handler(int num)
{
    if(num == SIGINT)
    {
        printf("\n\rTerminate all process");
        pthread_mutex_unlock(&i2c_mutex);
        pthread_mutex_unlock(&msg_queue_mutex);
        pthread_mutex_unlock(&log_file_mutex);
        mq_close(msg_queue_logger);
        mq_unlink("/msgqueue_logger");
        fclose(log_file);
        close(sockfd);                          
        exit(0);

    }
}

/***********************************************************************************************
 * @brief 
 *
 *
 *
 * @param address:
 *
 * @return 
 *********************************************************************************************/

void register_signal_handler()
{
    printf("\n\rEntering register signal handler");
    struct sigaction signals;
    signals.sa_flags = 0;
    signals.sa_handler = terminate_signal_handler;
    sigemptyset(&signals.sa_mask);
    sigaction(SIGINT,&signals,NULL);
    printf("\n\rExiting register signal handler");

}

void open_logger_message_queue()
{
    printf("\n\rEntering open logger message queue");
    struct mq_attr msg_queue_attr;
    msg_queue_attr.mq_maxmsg = MAX_MSG;
    msg_queue_attr.mq_msgsize = sizeof(log_msg_t);

    msg_queue_logger = mq_open("/msgqueue_logger", O_CREAT | O_RDWR, 0666,&msg_queue_attr);
    if(msg_queue_logger == -1)
    {
        printf("\n\rFailed to open logger message queue");
    }
    else
    {
        printf("\n\rLogger message queue opened successfully");
    }
    printf("\n\r Exiting open logger message queue");

}


void set_event(event_e event)
{

}