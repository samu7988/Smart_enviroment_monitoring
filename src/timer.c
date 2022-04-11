#include "timer.h"
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include "temperature_sensor.h"
#include "lux_sensor.h"
#include "i2c.h"
struct sigevent signal_spec;
timer_t timer_id;
struct itimerspec timer_setting;

void timer_handler(union sigval timer_data)
{
    printf("\n\rTimer is called every 5 sec");
	uint8_t data[2] = {0};
	bool status = i2c_read(LUX_SENSOR_ADDRESS,0x04,data,2);
    printf("\n\r After power on data read: data[0]:%u, data[1]:%u",data[0],data[1]);

	// double processed_val =0.0;
	// read_temperature_value(&processed_val,TEMP_CELSIUS);
	// printf("\n\rTemperature value: %lf",processed_val);
}


void time_create()
{
    signal_spec.sigev_notify = SIGEV_THREAD;
    signal_spec.sigev_notify_function = &timer_handler;
    signal_spec.sigev_value.sival_ptr = "Timer create";
	timer_create(CLOCK_REALTIME,&signal_spec,&timer_id);
	timer_setting.it_value.tv_sec =1;
	timer_setting.it_value.tv_nsec = 0;
	timer_setting.it_interval.tv_sec = 1;
	timer_setting.it_interval.tv_nsec = 0;
	timer_settime(timer_id,0,&timer_setting,NULL);
}
