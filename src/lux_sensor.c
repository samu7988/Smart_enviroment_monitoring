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
    uint8_t data[2] = {0x52,0x11};
    //uint16_t data = 0x11F0
    // status = i2c_read(LUX_SENSOR_ADDRESS,CONFIG_REG,data,2);
    // printf("\n\r before power on data read: data[0]:%u, data[1]:%u",data[0],data[1]);

    // data[0] &= ~(0x01);
    status = i2c_write(LUX_SENSOR_ADDRESS,CONFIG_REG,data,2);
    
    data[0] = 0x6f;
    data[1] = 0x5f;
    status = i2c_write(LUX_SENSOR_ADDRESS,0x01,data,2);

    uint8_t recv_data[2] = {0};
    status = i2c_read(LUX_SENSOR_ADDRESS, 0x01, recv_data,2);
    printf("\n\r Register 1 data: data[0]:%u, data[1]:%u",recv_data[0],recv_data[1]);

    return status;

}


bool read_light_value()
{

}

