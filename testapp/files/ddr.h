/****************************************************************************
 * @file:       ddr.h
 *
 * @Created:    30-04-2024
 *
 * @brief:      Header file for DDR interface.
 *
 * @Version:    1.0
 *
 * @Author:     Capgemini Engineering
 **************************************************************************/

/* Header FIles */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

/* Macros */
#define DIR_SUCCESS         0x00                /* Success code */
#define DIR_ERRLOG 	    printf              /* Macro for error messages */
#define DDR_TEST_SIZE	    (2 * 1024 * 1024)   /* Size of DDR test in bytes */
#define DIR_FAILURE	    -1                  /* Failure code */
#define DIR_INITVALUE	    0		        /* Initialization value */
#define DDR_MINSIZE	    1		        /* DDR minium size */
#define DDR_MAXSIZE	    (10 * 1024 * 1024)  /* DDR maximum size */

/*Function name:
 *      ddr_main - This function allocates memory dynamically in DDR memory and performs read and write operations.
 *
 * Parameters:
 *      None
 *
 * ReturnValue:
 *	DIR_SUCCESS - If the memory is allocated and able to write and read, function will return DIR_SUCCESS
 *	DIR_FAILURE - If the memory allocation is failed and unable to write and read, function will return DIR_FAILURE
*/
int ddr_main(void);

/*Function name:
 * 	writein_ddrmem - This function is used to write data into DDR memory.
 *
 * Parameters:
 * 	in_pDdrAddr, in_uiSize
 *
 * ReturnValue:
 *      DIR_SUCCESS - If the data write into the memory is succesful, function will return DIR_SUCCESS
 * 	DIR_FAILURE - If the data write into the memory is failed, function will return DIR_FAILURE
 */
short writein_ddrmem(uint8_t *in_pDdrAddr, unsigned int in_uiSize);

/*Function name:
 * 	readin_ddrmem - This function is used to read data from DDR memory
 *
 * Parameters:
 * 	in_pDdrAddr, in_uiSize
 *
 * ReturnValue:
 * 	DIR_SUCCESS - If the data read from the memory is successful, function will return DIR_SUCCESS
 * 	DIR_FAILURE - If the data read from the memory is failed, function will return DIR_FAILURE
 */
short readin_ddrmem(uint8_t *in_pDdrAddr, unsigned int in_uiSize);
