/*********************************************************************************************
 *@file:       registers.h
 *
 *@Created:    21-05-2024
 *
 *@brief:      This file implements to perform read/write operations on registers.
 *
 *@Version:    1.0
 *
 *@Author:     Capgemini Engineering
*********************************************************************************************/

/*Include files*/
#include <stdio.h>
#include <fcntl.h>
#include <asm/ioctl.h>
#include <unistd.h>
#include <stdint.h>

/* Macros */
/*node path, make sure to run mknod before this*/
#define Driver_path "/dev/ModuleDiagnostic"
#define DIR_SUCCESS 	      0
#define DIR_FAILURE 	      -1
#define DIR_LOG               printf         /* Macro for information messages */
#define DIR_ERRLOG            printf         /* Macro for error messages */

/*Function name:
 *    registers_main - This function perform 8,16,32 bit write and read operations on the registers.
 *
 *Parameters:
 *    None
 *
 *Return Value:
 *      DIR_SUCCESS - If the data read/write successfully, function will return DIR_SUCCESS
 *      DIR_FAILURE - If the driver failed to open, unable to perform read/write operations, it will return DIR_FAILURE
 */
int registers_main(void);
