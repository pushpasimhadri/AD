/**************************************************
 * @file:       testapp.h
 *
 * @Created:    17-04-2024
 *
 * @brief:      Header file of Interface testing
 *
 * @Version:    1.0
 *
 * @Author:     Capgemini Engineering
 **************************************************/

/*Include files*/
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <fcntl.h>
#include <asm/ioctl.h>
#include "i2c.h"
#include "spi.h"
#include "uart.h"
#include "ethernet.h"
#include "spi.h"
#include "ddr.h"
#include "registers.h"
#include "array_registers.h"
#include "AFDX_registers.h"

/* Macros */
#define PING_SUCCESS          0
#define DIR_LOG               printf         /* Macro for information messages */
#define DIR_ERRLOG            printf         /* Macro for error messages */ 

/*enums*/
enum event Menu;
enum Testcases Choice;

enum event
{
        SDF_FPGA_PS = 1,
        SDF_FPGA_PL = 2,
        DMB_FPGA_PS = 3,
        DAB_FPGA_PS = 4,
        DAB_FPGA_PL = 5,
        QUIT        = 6
};

enum Testcases
{
        UART_loopback = 1,
        QSPI_Interface_test,
        DDR4_Interface_test,
        I2C_Interface_test,
        Ethernet_loopback,
        AFDX_IP_CORE_test,
        MES_IP_CORE_test,
        Quit,
        Exit
};
