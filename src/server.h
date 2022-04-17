#ifndef SERVER_H_
#define SERVER_H_
/********************************************************************************************
*					FILENAME: .h
**********************************************************************************************/
/* Title: i2c.h
 * Brief:
 * Author: Sayali Mule
 * Date Created: March 09,2022
 * Course: Advanced Embedded Software Development
 

 * Reference[1]:
 * */
/****************************************************************************************
*					HEADER FILE SECTION
*****************************************************************************************/


/****************************************************************************************
*				     MACROS AND ENUMS
*****************************************************************************************/
#define MAX 80

/****************************************************************************************
*				GLOBAL VARIABLE SECTION
*****************************************************************************************/
extern int connfd;
/***************************************************************************************
*				FUNCTION PROTOTYPE
*****************************************************************************************/
bool server_init();


#endif //SERVER_H_
