/********************************************************************************************
*					FILENAME:i2c.c
**********************************************************************************************/
/* Title:i2c.c
 * Brief: Responsible for implementing basic i2c read and write operations.
 * Author:Sayali Mule
 * Date Created: April 09/2022
 * Course: Advanced Embedded Software Development
 * 

 * Reference[1]:
 * 
 * 
 * */
/****************************************************************************************
*					HEADER FILE SECTION
*****************************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include "i2c.h"
#include <linux/i2c.h>
/**************************************************************************************
*					GLOBAL VARIABLE
*******************************************************************************************/

/**********************************************************************************
*				FUNCTION DEFINITION
***************************************************************************************/

/***********************************************************************************************
 * @brief I2c read
 *
 *Responsible for implementing I2c read function
 *
 * @param address: address of pointer register TMP102
 *
 * @return status of I2C operation
 *********************************************************************************************/
bool i2c_read(uint8_t slave_address, uint8_t reg_addr,uint8_t* buffer,uint8_t num_bytes)
{   
    // to open actual I2C bus
    int fd = open("/dev/i2c-2", O_RDWR);

    if (fd < 0) 
    {
        printf("Error opening file: %s\n", strerror(errno));
        return 1;
    }

    // slave_address = (slave_address ) | (0x01);
    //to get the device from specific bus(specified from slave addr, and reg_address)
    // if (ioctl(fd, I2C_SLAVE, slave_address) < 0) 
    // {
    //     printf("ioctl error: %s\n", strerror(errno));
    //     return 1;
    // }
    // if(write(fd, &reg_addr, 1) < 0) //send reg address as 1st byte
    // {
    //     printf("write failed: %s\n",strerror(errno));
    //     return 1;
    // }
    // if(read(fd, buffer, num_bytes) < 0) //actual read
    // {
    //     printf("read failed: %s\n",strerror(errno));
    //     return 1;  
    // }



    int retval;
    struct i2c_msg msgs[2];
    struct i2c_rdwr_ioctl_data msgset[1];

    msgs[0].addr = slave_address;
    msgs[0].flags = 0;
    msgs[0].len = 1;
    msgs[0].buf = &reg_addr;

    msgs[1].addr = slave_address;
    msgs[1].flags = I2C_M_RD | I2C_M_NOSTART;
    msgs[1].len = 2;
    msgs[1].buf = buffer;

    msgset[0].msgs = msgs;
    msgset[0].nmsgs = 3;

    if (ioctl(fd, I2C_RDWR, &msgset) < 0) 
    {
        perror("ioctl(I2C_RDWR) in i2c_read");
        return -1;
    }

    for(int i = 0; i < num_bytes; i++)
    {
        printf("0x%02X\n", buffer[i]);
    }
 
    close(fd);

    return 0;}

/***********************************************************************************************
 * @brief I2c write
 *
 *Responsible for implementing I2c write function
 *
 * @param 
 *
 * @return status of I2C operation
 *********************************************************************************************/
bool i2c_write(uint8_t slave_address, uint8_t reg_addr,uint8_t* buffer, uint8_t num_bytes)
{   
    // to open the actual I2C bus
    int fd = open("/dev/i2c-2", O_RDWR);

    if (fd < 0) 
    {
        printf("Error opening file: %s\n", strerror(errno));
        return 1;
    }

    if (ioctl(fd, I2C_SLAVE, slave_address) < 0) 
    {
        printf("ioctl error: %s\n", strerror(errno));
        return 1;
    }

    uint8_t* data_to_send = malloc(sizeof(uint8_t) * (num_bytes + 1));
    if(data_to_send == NULL)
    {
        printf("Malloc failed :%s\n",strerror(errno));
        return 1;
    }

    data_to_send[0] = reg_addr;
    for(int i = 1; i <= num_bytes; i++)
    {
        data_to_send[i] = buffer[i - 1];
    }

    if(write(fd, data_to_send, (num_bytes+1)) < 0)  //actual write to write into the device
    {
        printf("write failed:%s\n",strerror(errno));
        return 1;
    } 
    
    free(data_to_send);   
    close(fd); 
    return 0;
}




