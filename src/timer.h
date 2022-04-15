#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdbool.h>


extern bool temp_sensor_time_expire;
extern bool light_sensor_time_expire;
void time_create();
void timer_handler();
double get_time();


#endif