/*********************************************************************************************
 *@file:       AFDX_registers.h
 *
 *@Created:    08-07-2024
 *
 *@brief:      This file implements to perform 32-bit read operation on registers.
 *
 *@Version:    1.0
 *
 *@Author:     Capgemini Engineering
*********************************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h> // for open
#include <errno.h> // for error codes
#include <asm/ioctl.h>

/* Macros */
#define Driver_path        "/dev/ModuleDiagnostic"
#define DIR_SUCCESS        0
#define DIR_FAILURE        -1
#define DIR_LOG            printf         /* Macro for information messages */
#define DIR_ERRLOG         printf         /* Macro for error messages */
#define OP_32BIT_READ      3

/* Structure to store memory operation details */
struct AFDX_mem {
    unsigned int operation;
    unsigned int address;
    unsigned int value;
};

/*Function name:
 *    AFDX_main - This function perform 32 bit read operation on the registers.
 *
 *Parameters:
 *    None
 *
 *Return Value:
 *      DIR_SUCCESS - If the data read successfully, function will return DIR_SUCCESS
 *      DIR_FAILURE - If the driver failed to open, unable to perform read operation, it will return DIR_FAILURE
 */
int AFDX_main(void);

