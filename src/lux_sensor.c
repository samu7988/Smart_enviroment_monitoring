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


bool enable_lightsensor()
{
    bool status = 0;
    uint8_t data[2] = {0x00,0x00};
    status = i2c_write(LUX_SENSOR_ADDRESS,CONFIG_REG,data,2);
    return status;

}

bool read_light_value(double* light_val)
{
	uint8_t data[2] = {0};
	bool status = i2c_read(LUX_SENSOR_ADDRESS,ALS_REG,data,2);
    printf("\n\r After power on data read: data[0]:%u, data[1]:%u",data[0],data[1]);
    uint16_t total_val = data[0] | (data[1] << 8);
    *light_val = (float)total_val * 0.0576;
    printf("\n\rCollected val: %lf",*light_val);
    return status;
}

