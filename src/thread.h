#ifndef THREAD_H_
#define THREAD_H_
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


/****************************************************************************************
*				     MACROS AND ENUMS
*****************************************************************************************/


/****************************************************************************************
*				GLOBAL VARIABLE SECTION
*****************************************************************************************/

/***************************************************************************************
*				FUNCTION PROTOTYPE
*****************************************************************************************/
void* temperature_sensor_thread();
void* light_sensor_thread();
void* log_thread(void* arg);
void* server_thread();


#endif //I2C_H_
