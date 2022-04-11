/**
* Simple example for C project build
*/

#include <stdio.h>
#include "timer.h"
#include "i2c.h"
#include <stdint.h>
#include "temperature_sensor.h"
#include "lux_sensor.h"

#define TEMP_SENSOR_ADDRESS (0x48)
#define THIGH_REG		(0x03)
int main(void)
{
	// uint8_t buffer[2] = {0xFE, 0x8A};
	// uint8_t receive_data[2] = {0};
	// i2c_write(TMP102_SENSOR_ADDRESS,THIGH_REG, buffer, 2);
	// i2c_read(TMP102_SENSOR_ADDRESS,THIGH_REG,receive_data,2);
	// for(int i = 0; i < 2; i++)
	// {
	// 	printf("\n\rReceive data: %u",receive_data[i]);
	// }

	enable_lux_sensor();
	time_create();

	printf("Hello and welcome to ECEN5013!\n");
	while(1);
}
