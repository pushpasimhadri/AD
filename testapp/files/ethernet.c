/****************************************************************************
 * @file:        ethernet.c
 *
 * @brief:       This file implements loopback test for Ethernet interface.
 *
 * @Created:     17-04-2024
 *
 * @Version:     1.0
 *
 * @Author:      Capgemini Engineering
 ****************************************************************************/

#include "ethernet.h"

/*Function name:
 * 	ping_ip - Execute a ping command to the specified IP address.
 *
 * 	parameters - ip_address
 *
 * 	Return value:
 * 		void
 */
void ping_ip(const char *ip_address) 
{
	int l_status = 0;
	/* Execute the ping command */
	char command[COMMAND_SIZE];
	snprintf(command, sizeof(command), "ping -c 4 %s", ip_address);
	DIR_LOG("Executing command: %s\n", command);
	
	/* Execute the ping command using the system function */
	l_status = system(command);
	
	/* Check if the system call failed */
	if (l_status == ERROR_STATUS)
	{
		DIR_ERRLOG("Error executing ping command");
	}
	/* Check if the ping command executed but returned a non-zero status code */
	else if (WIFEXITED(l_status) && WEXITSTATUS(l_status) != 0)
	{
		DIR_LOG(stderr, "Ping command exited with non-zero status\n");
	}
	else
		printf("Ping Successfully\n");
}

/* Function name
 * 	ethernet_main - This function performs loopback test for ethernet interface.
 *
 * parameters
 * 	The number of command-line arguments.
 * 	The array of command-line arguments.
 *
 * Return value
 * 	DIR_SUCCESS - If the loopback test is successful, it will return DIR_SUCCESS
 * 	ERROR_STATUS - If the IP address length is invalid, it will return ERROR_STATUS
 */
int ethernet_main(char *argv) 
{
    DIR_LOG("IP Address: %s\n", argv);
    /* Check the length of the input IP address */
    if (strlen(argv) > MAX_IP_LENGTH) 
    {
        DIR_ERRLOG(stderr, "Error: Invalid IP address length\n");
	return ERROR_STATUS; 
    }

    ping_ip(argv);

    return DIR_SUCCESS;
}
