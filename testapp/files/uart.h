/***************************************************
 * @file      uart.h
 *
 * @brief     Header file for UART loopback test.
 *
 * @Version   1.0
 *
 * @Author    Capgemini Engineering
 ***************************************************/

/* Header FIles */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/select.h>
 
/* Macros */
#define UART_DEVICE "/dev/tty*"   /* Input from the User*/
#define BAUD_RATE 115200
#define BUFFER_SIZE 256
#define TIMEOUT_MICROSECONDS 0
#define TIMEOUT_SEC 1
#define DIR_SUCCESS 0x00
#define DIR_LOG printf         /* Macro for information messages */
#define LISTEN_FROM_DEVICE 1
#define LISTEN_FROM_TTY_TO_DEVICE 2
#define EXIT 3
#define ERROR_OCCURRED -1

/*Function name:
 * uart_main - This function performs a loopback test on UART communication.
 *
 * Parameters:
 *      None
 *
 * ReturnValue:
 *      i. If the value is 0, the function returns successful.
 *      ii. If the value is not zero, then the function returns with an error code.
 */

int uart_main();
