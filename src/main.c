/**
* Simple example for C project build
*/

#include <stdio.h>
#include "timer.h"
#include "i2c.h"
#include <stdint.h>
#include "temperature_sensor.h"
#include "lux_sensor.h"
#include "server.h"
#include <pthread.h>
#include "thread.h"
#include "synchronization.h"
#define TEMP_SENSOR_ADDRESS (0x48)
#define THIGH_REG		(0x03)
int main(int argc, char** argv)
{
	// uint8_t buffer[2] = {0xFE, 0x8A};
	// uint8_t receive_data[2] = {0};
	// i2c_write(TMP102_SENSOR_ADDRESS,THIGH_REG, buffer, 2);
	// i2c_read(TMP102_SENSOR_ADDRESS,THIGH_REG,receive_data,2);
	// for(int i = 0; i < 2; i++)
	// {
	// 	printf("\n\rReceive data: %u",receive_data[i]);
	// }

	enable_lightsensor();
	time_create();
	register_signal_handler();
	open_logger_message_queue();

	server_init();
	pthread_t temperature_thread;
	pthread_t light_thread;
	pthread_t logger_thread;
	pthread_t serv_thread;

	pthread_create(&temperature_thread, NULL, temperature_sensor_thread, NULL);
	pthread_create(&light_thread, NULL, light_sensor_thread, NULL);
	pthread_create(&logger_thread, NULL, log_thread, argv[1]);
	pthread_create(&serv_thread, NULL, server_thread, NULL);

	pthread_join(temperature_thread, NULL);
	pthread_join(light_thread, NULL);
	pthread_join(logger_thread, NULL);
	pthread_join(serv_thread, NULL);

	printf("Hello and welcome to ECEN5013!\n");
	while(1);
}





