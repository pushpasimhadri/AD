/******************************************************
 * @file:       ethernet.h
 *
 * @Created:    17-04-2024
 *
 * @brief:      This file implements loopback test for Ethernet interface.
 *
 * @Version:    1.0
 *
 * @Author:     Capgemini Engineering
 ******************************************************/

/* Header FIles */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* Macros */
#define MAX_IP_LENGTH         15            /* Maximum length of an IPv4 address (including null terminator) */
#define DIR_SUCCESS           0x00          /* Success code */
#define COMMAND_SIZE          100           /* Size of the command buffer */
#define DIR_LOG               printf        /* Macro for information messages */
#define DIR_ERRLOG            printf        /* Macro for error messages */
#define ERROR_STATUS          -1

/*Function name:
 *      ping_ip - Execute a ping command to the specified IP address.
 *
 *      parameters - ip_address
 *
 *      Return value:
 *              void
 */
void ping_ip(const char *ip_address);

/* Function name
 *      ethernet_main - This function performs loopback test for ethernet interface.
 *
 * parameters
 *      The number of command-line arguments.
 *      The array of command-line arguments.
 *
 * Return value
 *      DIR_SUCCESS - If the loopback test is successful, it will return DIR_SUCCESS
 *      ERROR_STATUS - The IP address length is invalid, it will return ERROR_STATUS
 */
int ethernet_main(char *argv);
