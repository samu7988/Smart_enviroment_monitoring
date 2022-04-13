#make all or make => then gcc will be used
#make CROSS_COMPILE=aarch64-none-linux-gnu-

CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Werror
SRCS = main.c timer.c i2c.c temperature_sensor.c lux_sensor.c
CLIENT_SRC = client.c
LIBRARY = -lpthread -lrt -lm
OBJS = $(SRCS:.c=.o) #replace .c file 
TARGET = smart_environment #$(SRCS:.c=) #replace .c with nothing"" for eg. writer.c => writer
CLIENT = client

all: $(TARGET) 
client: $(CLIENT)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBRARY)

.c.o:
	$(CC) -c  $(SRCS) 


ifeq ($(CC),gcc)
$(CLIENT):
		gcc -c $(CLIENT_SRC)
		gcc $(CFLAGS) -o $(CLIENT) client.o $(LIBRARY)
endif

clean:
	rm -f $(TARGET) *.o $(CLIENT)
