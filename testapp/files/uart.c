/***************************************************************************
 * @file          uart.c
 *
 * @brief         This file implements loopback test for UART interface.
 *
 * @Version       1.0
 *
 * @Author        Capgemini Engineering
 *
 ***************************************************************************/

#include "uart.h"

/*Function name:
 * set_uart_config - This function sets the UART Configurations.
 *
 * Parameters: 
 * 	uart_fd
 *
 * ReturnValue:
 * 	Returns 0
 */

void set_uart_config(int uart_fd) {
    struct termios uart_config;
    tcgetattr(uart_fd, &uart_config);
    cfsetospeed(&uart_config, BAUD_RATE);
    cfsetispeed(&uart_config, BAUD_RATE);
    uart_config.c_cflag |= (CLOCAL | CREAD); // Enable receiver and set local mode
    uart_config.c_cflag &= ~PARENB;          // No parity
    uart_config.c_cflag &= ~CSTOPB;          // 1 stop bit
    uart_config.c_cflag &= ~CSIZE;
    uart_config.c_cflag |= CS8;              // 8 data bits
    uart_config.c_cc[VMIN] = 0;              // Read returns immediately
    uart_config.c_cc[VTIME] = 0;             // Timeout disabled
    tcsetattr(uart_fd, TCSANOW, &uart_config);
}

/*Function name:
 * read_and_echo - This function reads the input from the given file descriptor and echo to the UART device.
 *
 * Parameters:
 * 	uart_fd,input_fd
 *
 * ReturnValue:
 * 	Returns 0
 */
void read_and_echo(int uart_fd, int input_fd) 
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Check for input from the given file descriptor
    bytes_read = read(input_fd, buffer, BUFFER_SIZE);
    if (bytes_read > 0) 
    {
        printf("Received data: %.*s\n", (int)bytes_read, buffer);
        printf("Echoing data to the other side...\n");
        write(uart_fd, buffer, bytes_read); // Echo to UART device
    }
}

/*Function name:
 * uart_main - This function performs a loopback test on UART communication.
 *
 * Parameters: 
 * 	None
 *
 * ReturnValue:
 * 	i. If the value is 0, the function returns successful.
 * 	ii. If the value is not zero, then the function returns with an error code.
 */

int uart_main() 
{
    int uart_fd;
    fd_set read_fds;
    struct timeval timeout;
    int option;

    // Open UART device
    uart_fd = open(UART_DEVICE, O_RDWR | O_NOCTTY);
    if (uart_fd == ERROR_OCCURRED) 
    {
        perror("Error opening UART device");
        return 1;
    }

    // Configure UART
    set_uart_config(uart_fd);

    // Menu loop
    while (1) 
    {
        // Display menu
        DIR_LOG("Menu:\n");
        DIR_LOG("1. Listen from device to ttyS2\n");
        DIR_LOG("2. Listen from ttyS2 to device\n");
        DIR_LOG("3. Exit\n");
        DIR_LOG("Enter your choice: ");
        scanf("%d", &option);

        if (option == EXIT) 
	{
            break; // Exit loop
        }

        // Clear the file descriptor set
        FD_ZERO(&read_fds);

        // Add file descriptor to the set
        FD_SET(uart_fd, &read_fds); 

        // Set timeout
        timeout.tv_sec = TIMEOUT_SEC;
        timeout.tv_usec = TIMEOUT_MICROSECONDS;

        // Wait for activity on file descriptor
        if (select(uart_fd + 1, &read_fds, NULL, NULL, &timeout) == ERROR_OCCURRED) 
	{
            perror("select");
            break;
        }

        // Check for activity on UART based on the option
        switch (option) 
	{
            case LISTEN_FROM_DEVICE: // Listen from device to ttySession
                read_and_echo(uart_fd, STDIN_FILENO);
                break;
            case LISTEN_FROM_TTY_TO_DEVICE: // Listen from ttySession to device
                read_and_echo(uart_fd, uart_fd);
                break;
            default:
                printf("Invalid option. Please enter a valid option.\n");
                break;
        }
    }

    // Close UART device
    close(uart_fd);

    return DIR_SUCCESS;
}
