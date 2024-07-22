/*********************************************************************************************
 *@file:       crc_core.h
 *
 *@Created:    18-07-2024
 *
 *@brief:      This file implements to calculate CRC.
 *
 *@Version:    1.0
 *
 *@Author:     Capgemini Engineering
*********************************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h> // for open
#include <errno.h> // for error codes

#define POLYNOMIAL         0x04C11DB7
#define DIR_SUCCESS        0
#define DIR_FAILURE        -1
#define DIR_LOG            printf         /* Macro for information messages */
#define DIR_ERRLOG         printf         /* Macro for error messages */

/*Function name:
 *    crc_main - This function implements to calculate crc.
 *
 *Parameters:
 *    None
 *
 *Return Value:
 *      DIR_SUCCESS - If the crc for the data and Block Id, Block length calculated successfully, function will return DIR_SUCCESS
 *      DIR_FAILURE - If the entered data is invalid, it will return DIR_FAILURE
 */
int crc_main();
