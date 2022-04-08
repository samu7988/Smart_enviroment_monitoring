#include<stdio.h>
#include <syslog.h>

void main()
{
	openlog("Hello world", LOG_DEBUG, LOG_DAEMON);
 	printf("sayali helloworld");	
	syslog(LOG_ERR,"Hello world\n\r");
        closelog();
   
   
}
