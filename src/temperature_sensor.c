/********************************************************************************************
*					FILENAME:temperature_sensor.c
**********************************************************************************************/
/* Title:temperature_sensor.c 
 * Brief:Create functionality to read temperature value and other TMP102 sensor related functionality 
 * Author: Sayali Mule
 * Date Created: April 9, 2022
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
#include "temperature_sensor.h"
#include <stdio.h>
#include <pthread.h>
#include "synchronization.h"
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

bool temperature_write_register(uint8_t reg_address,uint8_t* data, uint8_t num_bytes)
{
    bool status = 0;
    status = i2c_write(TMP102_SENSOR_ADDRESS,reg_address,data, num_bytes);
    if(status == 1)
    {
        printf("\n\rtemperature_write_register() failed");
        return 1;
    }
    return status;
}

bool process_raw_temp_values(uint8_t* data, double* human_readable_val, temp_unit_type_t temp_unit)
{
    int32_t digital_val = 0;
    //12 bit: Bit 0 of second byte is 0
    //13 bit: Bit 0 of second byte is 1

    double multiplier = 0.0625;

    if(data[0] & 1) //13 bit mode
    {
        digital_val = (data[1] << 5) | (data[0] >> 3);

        if(digital_val > 0xFFF)
        {
            digital_val |= 0xE000;
        }
    }
    else //12 bit mode
    {
        digital_val = (data[1] << 4) | (data[0] >> 4);
        if(digital_val > 0x7FFF)
        {
            digital_val |= 0xF000;
        }
    }

    if(temp_unit == TEMP_KELVIN)
    {
        *human_readable_val = (digital_val * multiplier) + 273.15;
    }
    else if(temp_unit == TEMP_FAHRENHEIT)
    {
        *human_readable_val = (digital_val * multiplier * 9.0/5.0) + 32.0;
    }
    else
    {
        *human_readable_val = digital_val * multiplier;
    }

    return 0;
}

bool read_temperature_value(double* processed_value, temp_unit_type_t request)
{
    bool status = 0;
    uint8_t data[2] = {0};
    pthread_mutex_lock(&i2c_mutex);

    status = i2c_read(TMP102_SENSOR_ADDRESS,TEMPERATURE_REGISTER,data,2);
    if(status == 1)
    {
        printf("\n\rread_temperature_value() failed");
        pthread_mutex_unlock(&i2c_mutex);
        return status;
    }

    //swap values for further processing 
    data[0] = data[0] ^ data[1];
    data[1] = data[0] ^ data[1];
    data[0] = data[0] ^ data[1];

    status = process_raw_temp_values(data,processed_value,request);
    pthread_mutex_unlock(&i2c_mutex);
    return status;
}