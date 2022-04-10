/********************************************************************************************
*					FILENAME:lux_sensor.c
**********************************************************************************************/
/* Title: lux_sensor.c 
 * Brief: Responsible for implementing functionality to read and write lux sensor
 * Author: Sayali Mule
 * Date Created: April 10, 2022
 * Course: Advanced Embedded Software Development
 * Project: 1

 * Reference[1]: 
 * 
 * 
 * */
/****************************************************************************************
*					HEADER FILE SECTION
*****************************************************************************************/
#include "i2c.h"
#include "lux_sensor.h"
#include <stdio.h>
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
bool enable_lux_sensor()
{
    bool status = 0;
    uint8_t data[2] = {0};
    status = i2c_read(LUX_SENSOR_ADDRESS,CONFIG_REG,data,2);
    printf("\n\r before power on data read: data[0]:%u, data[0]:%u",data[0],data[1]);
    data[0] &= ~(0x01);
    status = i2c_write(LUX_SENSOR_ADDRESS,CONFIG_REG,data,2);
    
    status = i2c_read(LUX_SENSOR_ADDRESS,CONFIG_REG,data,2);
    printf("\n\r After power on data read: data[0]:%u, data[0]:%u",data[0],data[1]);
    return status;

}


bool read_light_value()
{

}

