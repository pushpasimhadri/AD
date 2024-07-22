/*********************************************************************************************
 *@file:       i2c.c
 *
 *@Created:    23-04-2024
 *
 *@brief:      This file implements to read the values from M24C64 EEPROM.
 *
 *@Version:    1.0
 *
 *@Author:     Capgemini Engineering
 *********************************************************************************************/

#include "i2c.h"

int g_i2c_fd;

/*Function name:
 *    readdata - This function perform write and read operations from the M24C64 EEPROM.
 *
 *Parameters:
 *    None
 *
 *Return Value:
 *      DIR_SUCCESS   - If the data is successfully read from EEPROM, function will return DIR_SUCCESS
 *      EEPROM_WERROR - Failed to write the data into the EEPROM
 *	EEPROM_RERROR - Failed to read the data from the EEPROM
 */
int readdata(void) 
{
	uint8_t eeprom_buffer[EEPROM_DATA_SIZE];    

	/* write command to select the eeprom register */
	if(write(g_i2c_fd, (void *)EEPROM_REG_ADDR,BYTE_LENGTH) !=BYTE_LENGTH) 
	{
		DIR_ERRLOG("Failed to set pointer address\n");
		return EEPROM_WERROR;
	}
       	else
		DIR_LOG("ACCESS the EEPROM register successfully\n");

	usleep(MICROSECOND);

	/* Read eeprom data */
	if (read(g_i2c_fd, eeprom_buffer, EEPROM_DATA_SIZE) !=EEPROM_DATA_SIZE) 
	{
		DIR_ERRLOG("Failed to read from the I2C bus\n");
		return EEPROM_RERROR;
	}
	else
		DIR_LOG("ACCESS the EEPROM buffer successfully \n");

	return DIR_SUCCESS;
}

/*Function name:
 *      i2c_main - This function reads the data from the M24C64 EEPROM.
 *
 * Parameters:
 *      None
 *
 *ReturnValue:
 *	DIR_SUCCESS  - If the data is read from EEPROM succesfully, function will return DIR_SUCCESS
 *	FILE_OERROR  - Failed to open the I2C bus
 *	SLAVE_AERROR - Failed to access slave address
 */
int i2c_main(void) 
{
	int l_i=0;
	unsigned char buffer[10];

	/* Open I2C device */
	if ((g_i2c_fd = open(I2C_DEV_PATH, O_RDWR)) < OPEN_SUCCESS) 
	{
		DIR_ERRLOG("Failed to open the I2C bus");
		return FILE_OERROR;
	}
	else
		DIR_LOG("dev path opened successfully \n");

	/* Set I2C device address */
	if(ioctl(g_i2c_fd, I2C_SLAVE_FORCE, EEPROM_ADDR) < OPEN_SUCCESS) 
	{
		DIR_ERRLOG("Failed to acquire bus access and/or talk to slave \n");
		return SLAVE_AERROR;
	}
	else
		DIR_LOG("Access the I2c bus successfully \n");

	/* Read data from EEPROM
	Reading 10 bytes of data starting from address 0x00 */

	if(read(g_i2c_fd, buffer, 10) !=10) {
		perror("Failed to read from the device.");
		exit(1);
	}
	/* Display read data */
	DIR_LOG("Data read from EEPROM:\n");

	for(l_i=0;l_i<10;l_i++) {
		printf("%02x", buffer[l_i]);
	}
	DIR_LOG("\n");

	/* Close I2C device */
	close(g_i2c_fd);

	return DIR_SUCCESS;
}
