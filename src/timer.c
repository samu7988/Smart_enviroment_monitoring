#include "timer.h"
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include "temperature_sensor.h"
#include "lux_sensor.h"
#include "i2c.h"

bool temp_sensor_time_expire = 0;
bool light_sensor_time_expire = 0;
struct sigevent signal_spec;
timer_t timer_id;
struct itimerspec timer_setting;

void timer_handler(union sigval timer_data)
{


	// double processed_val =0.0;
	// read_temperature_value(&processed_val,TEMP_CELSIUS);
	// printf("\n\rTemperature value: %lf",processed_val);
	// double light_val = 0.0;
	// read_light_value(&light_val);
	printf("\n\rTimer is firing every 5 second");
	temp_sensor_time_expire = 1;
	light_sensor_time_expire = 1;
	
}


void time_create()
{
    signal_spec.sigev_notify = SIGEV_THREAD;
    signal_spec.sigev_notify_function = &timer_handler;
    signal_spec.sigev_value.sival_ptr = "Timer create";
	timer_create(CLOCK_REALTIME,&signal_spec,&timer_id);
	timer_setting.it_value.tv_sec =5;
	timer_setting.it_value.tv_nsec = 0;
	timer_setting.it_interval.tv_sec = 5;
	timer_setting.it_interval.tv_nsec = 0;
	timer_settime(timer_id,0,&timer_setting,NULL);
}


double get_time()
{
	struct timespec current_time;
	clock_gettime(CLOCK_MONOTONIC, &current_time);
	return ((current_time.tv_sec * (1000.0)) + (current_time.tv_nsec/1000000.0));
}