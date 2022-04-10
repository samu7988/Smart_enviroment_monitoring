#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_
/********************************************************************************************
*					FILENAME: temperature_sensor.h
**********************************************************************************************/
/* Title: temperature_sensor.h
 * Brief: Create functionality to read temperature value and other TMP102 sensor related functionality
 * Author: Sayali Mule
 * Date Created: March 09,2022
 * Course: Advanced Embedded Software Development
 

 * Reference[1]:
 * */
/****************************************************************************************
*					HEADER FILE SECTION
*****************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
/****************************************************************************************
*				     MACROS AND ENUMS
*****************************************************************************************/
#define TMP102_SENSOR_ADDRESS (0x48)
#define TEMPERATURE_REGISTER   (0x00)

typedef enum
{
    TEMP_KELVIN,
    TEMP_FAHRENHEIT,
    TEMP_CELSIUS
}temp_unit_type_t;
/****************************************************************************************
*				GLOBAL VARIABLE SECTION
*****************************************************************************************/

/***************************************************************************************
*				FUNCTION PROTOTYPE
*****************************************************************************************/
bool read_temperature_value(double* processed_value, temp_unit_type_t request);
bool process_raw_temp_values(uint8_t* data, double* human_readable_val, temp_unit_type_t temp_unit);
bool temperature_write_register(uint8_t reg_address,uint8_t* data, uint8_t num_bytes);

#endif //TEMPERATURE_H_
