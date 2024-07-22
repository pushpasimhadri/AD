/**
 * @file        spi.c
 *
 * @brief       This file implements to read and write the values from EEPROM
 *
 * @Version       1.0
 *
 * @Author        Capgemini Engineering
 *
 */


#include "spi.h"

/*Function name:
 * 	eeprom_main - This function read and write the values from 25CSM04 EEPROM
 * 		      using SPI communication.
 *
 * Parameters:
 * 	None
 *
 * ReturnValue:
 * 	i. If the value is 0, the function returns successful.
 * 	ii. If the value is not zero, then the function return with the error code.
 */
int eeprom_main() 
{
    int spi_fd;
    uint32_t tx_data, rx_data;
    uint8_t spi_mode_value = SPI_MODE;
    struct spi_ioc_transfer spi_transfer = 
    {
        .tx_buf = (unsigned long)&tx_data,
        .rx_buf = (unsigned long)&rx_data,
        .len = SIZE,  // 32 bits
        .speed_hz = SPI_SPEED,
        .bits_per_word = SPI_BITS_PER_WORD,
    };

    // Open SPI device
    spi_fd = open(SPI_DEVICE, O_RDWR);
    if (spi_fd < 0) 
    {
        perror("Error opening SPI device");
        exit(1);
    }

    // Set SPI mode
    if (ioctl(spi_fd, SPI_IOC_WR_MODE, &spi_mode_value) < 0) 
    {
        perror("Error setting SPI mode");
        close(spi_fd);
        exit(1);
    }

    // Read EEPROM values
    for (int i = 0; i < EEPROM_SIZE; i++) 
    {
        // Construct the instruction code and address
        tx_data = (EEPROM_READ_INSTRUCTION  << 24) | (i & 0xFFFFFF);

        // Perform SPI transfer
        if (ioctl(spi_fd, SPI_IOC_MESSAGE(1), &spi_transfer) < 0) 
	{
            perror("Error in SPI transfer");
            close(spi_fd);
            exit(1);
        }

        // Print the address and received value
        printf("Address: %d, Value: %d\n", i, rx_data & 0xFF);
    }

    // Close SPI device
    close(spi_fd);

    return DIR_SUCCESS;
}
