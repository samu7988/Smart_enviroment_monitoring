#include "timer.h"
#include <stdio.h>
#include <signal.h>
#include <time.h>

struct sigevent signal_spec;
timer_t timer_id;
struct itimerspec timer_setting;

void timer_handler(union sigval timer_data)
{
    printf("\n\rTimer is called every 5 sec");
}


void time_create()
{
    signal_spec.sigev_notify = SIGEV_THREAD;
    signal_spec.sigev_notify_function = &timer_handler;
    signal_spec.sigev_value.sival_ptr = "Timer create";
	timer_create(CLOCK_REALTIME,&signal_spec,&timer_id);
	timer_setting.it_value.tv_sec =1;
	timer_setting.it_value.tv_nsec = 0;
	timer_setting.it_interval.tv_sec = 5;
	timer_setting.it_interval.tv_nsec = 0;
	timer_settime(timer_id,0,&timer_setting,NULL);
}
