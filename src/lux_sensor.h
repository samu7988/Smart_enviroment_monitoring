#ifndef LUX_SENSOR_H_
#define LUX_SENSOR_H_
/********************************************************************************************
*					FILENAME: lux_sensor.h
**********************************************************************************************/
/* Title: lux_sensor.h
 * Brief: Responsible for implementing functionality to read light sensor
 * Author: Sayali Mule
 * Date Created: March 09,2022
 * Course: Advanced Embedded Software Development
 

 * Reference[1]:
 * */
/****************************************************************************************
*					HEADER FILE SECTION
*****************************************************************************************/
#include <stdbool.h>
#include <stdint.h>

/****************************************************************************************
*				     MACROS AND ENUMS
*****************************************************************************************/
#define LUX_SENSOR_ADDRESS (0x10)
#define CONFIG_REG         (0x00)

/****************************************************************************************
*				GLOBAL VARIABLE SECTION
*****************************************************************************************/

/***************************************************************************************
*				FUNCTION PROTOTYPE
*****************************************************************************************/
bool enable_lux_sensor();

#endif //LUX_SENSOR_H_
