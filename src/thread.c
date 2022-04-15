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
    double temperature = 0.0;
    double current_time = 0.0;
    while(1)
    {
        if(temp_sensor_time_expire == 1)
        {
            current_time = get_time();
            status = read_temperature_value(&temperature,TEMP_CELSIUS);

            if(status)
            {
                printf("\n\rread_temperature_value() returned 1");
            }

            printf("\n\r[%lf]Temperature value: %lf",current_time,temperature);
            temp_sensor_time_expire = 0;
        }
    }
}


void* light_sensor_thread()
{
    bool status = 0;
    double light_value = 0.0;
    double current_time = 0.0;
    while(1)
    {
        if(light_sensor_time_expire == 1)
        {
            current_time = get_time();
            status = read_light_value(&light_value);

            if(status)
            {
                printf("\n\rread_light_value() returned 1");
            }

            printf("\n\r[%lf]light value: %lf",current_time,light_value);
            light_sensor_time_expire = 0;
        }
    }
}