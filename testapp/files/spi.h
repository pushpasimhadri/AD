/**
 * @file       spi.h
 *
 * @brief     Header file for SPI Interface
 *
 * @Version   1.0
 *
 * @Author    Capgemini Engineering
 *
 */ 


/* Header FIles */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

/* Macros */
#define SPI_DEVICE          "/dev/spidev0.0"  // Update this according to your SPI device
#define SPI_MODE            SPI_MODE_0         // SPI Mode
#define SPI_BITS_PER_WORD   8                  // Number of bits per word
#define SPI_SPEED           1000000            // SPI speed (1 MHz in this example)
#define DIR_SUCCESS         0x00               /* Success code */
#define DIR_ERRLOG printf                      /* Macro for error messages */
#define EEPROM_SIZE         256                // Size of EEPROM in bytes
#define SIZE                4	               // Size of SPI transfer
#define EEPROM_READ_INSTRUCTION 0x03           // Instruction code for EEPROM read operation 

/*Function name:
 *      eeprom_main - This function read and write the values from 25CSM04 EEPROM
 *                    using SPI communication.
 *
 * Parameters:
 *      None
 *
 * ReturnValue:
 *      i. If the value is 0, the function returns successful.
 *      ii. If the value is not zero, then the function return with the error code.
 */
int eeprom_main();
