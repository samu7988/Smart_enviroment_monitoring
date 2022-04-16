#ifndef SYNCHRONIZATION_H_
#define SYNCHRONIZATION_H_
/********************************************************************************************
*					FILENAME: .h
**********************************************************************************************/
/* Title: i2c.h
 * Brief:
 * Author: Sayali Mule
 * Date Created: March 09,2022
 * Course: Advanced Embedded Software Development
 

 * Reference[1]:
 * */
/****************************************************************************************
*					HEADER FILE SECTION
*****************************************************************************************/
#include <mqueue.h>


/****************************************************************************************
*				     MACROS AND ENUMS
*****************************************************************************************/
typedef enum
{
    TEMPERATURE_SENSOR,
    LIGHT_SENSOR
}thread_id_e;


typedef struct
{
    double time;
    double sensor_val;
    thread_id_e id;
}log_msg_t;

/****************************************************************************************
*				GLOBAL VARIABLE SECTION
*****************************************************************************************/
extern pthread_mutex_t i2c_mutex ;
extern pthread_mutex_t msg_queue_mutex ;
extern pthread_mutex_t log_file_mutex;
extern mqd_t* msg_queue_logger;
extern FILE* log_file;
/***************************************************************************************
*				FUNCTION PROTOTYPE
*****************************************************************************************/
void register_signal_handler();
void open_logger_message_queue();

#endif //I2C_H_
