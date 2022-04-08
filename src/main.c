#include <stdio.h>
#include <syslog.h>

int main(char argc, char* argv[])
{
	openlog("Hello world", LOG_DEBUG, LOG_DAEMON);
 	printf("sayali helloworld");	
	syslog(LOG_ERR,"Hello world\n\r");
        closelog();
   	return 0;
   
}
