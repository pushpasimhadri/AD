/*****************************************************
 * @file:          i2c.h
 *
 * @Created:       23-04-2024
 *
 * @brief:         This file implements to read the values from M24C64 EEPROM.
 *
 * @Version:       1.0
 *
 * @Author:        Capgemini Engineering
 ****************************************************/

/* Header FIles */
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

/* Macros */
#define I2C_DEV_PATH          "/dev/i2c-1"   /* Path to the I2C device */
#define EEPROM_ADDR           0x50           /* I2C device address */
#define EEPROM_REG_ADDR       0x00           /* Address of eeprom register */
#define DIR_SUCCESS           0x00           /* Success code */
#define FILE_OERROR           0x01           /* Open file error code */ 
#define SLAVE_AERROR          0x02           /* Error code for access slave address */
#define EEPROM_RERROR         0x03           /* Error code for eeprom read */
#define EEPROM_WERROR         0x05           /* Error code for eeprom write */
#define DIR_LOG               printf         /* Macro for information messages */
#define DIR_ERRLOG            printf         /* Macro for error messages */
#define BYTE_LENGTH           1
#define MICROSECOND           1000000
#define EEPROM_DATA_SIZE      2
#define OPEN_SUCCESS          0

/*Function name:
 *    readdata - This function perform write and read operations from the M24C64 EEPROM.
 *
 *Parameters:
 *    None
 *
 *Return Value:
 *    DIR_SUCCESS   - If the data is successfully read from EEPROM, function will return DIR_SUCCESS
 *    EEPROM_WERROR - Failed to write the data into the EEPROM
 *    EEPROM_RERROR - Failed to read the data from the EEPROM
 */
int readdata(void);

/*Function name:
 *      i2c_main - This function reads the data from the M24C64 EEPROM.
 *
 * Parameters:
 *      None
 *
 *ReturnValue:
 *      DIR_SUCCESS  - If the data is read from EEPROM succesfully, function will return DIR_SUCCESS
 *      FILE_OERROR  - Failed to open the I2C bus
 *      SLAVE_AERROR - Failed to access slave address  
 */
int i2c_main(void);
