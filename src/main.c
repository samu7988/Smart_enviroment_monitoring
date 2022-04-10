/**
* Simple example for C project build
*/

#include <stdio.h>
#include "timer.h"
#include "i2c.h"
#include <stdint.h>

#define TEMP_SENSOR_ADDRESS (0x48)
#define THIGH_REG		(0x03)
int main(void)
{
	uint8_t buffer[2] = {0xFE, 0x8A};
	uint16_t receive_data = 0;
	i2c_write(TEMP_SENSOR_ADDRESS,THIGH_REG, buffer, 2);
	i2c_read(TEMP_SENSOR_ADDRESS,THIGH_REG,&receive_data,2);
	printf("\n\rMain receive data: %x", receive_data);
	//time_create();
	printf("Hello and welcome to ECEN5013!\n");
	while(1);
}
