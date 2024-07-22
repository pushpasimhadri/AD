/****************************************************************************
 * @file:       ddr.c
 *
 * @Created:    30-04-2024
 *
 * @brief       To verify PS DDR memory by write and read.
 *
 * @Version:    1.0
 *
 * @Author      Capgemini Engineering
 **************************************************************************/

#include "ddr.h"

/*Function name:
 * 	ddr_main - This function allocates memory dynamically in DDR memory and performs read and write operations.
 *
 * Parameters:
 * 	None
 *
 * ReturnValue:
 * 	DIR_SUCCESS - If the memory is allocated and able to write and read, function will return DIR_SUCCESS
 * 	DIR_FAILURE - If the memory allocation is failed and unable to write and read, function will return DIR_FAILURE
 */

int ddr_main(void) 
{
	uint8_t *pDdrMem = NULL;
	int16_t l_sRetVal = DIR_SUCCESS;
	
	/* Allocate 1MB memory for DDR Test */
	pDdrMem = malloc(DDR_TEST_SIZE);
	if(pDdrMem == NULL)
	{
		DIR_ERRLOG("ERROR:\t Memory allocation failed\n");
		return DIR_FAILURE;
	}

	/* Function call to write in DDR memory */
	l_sRetVal = writein_ddrmem(pDdrMem, DDR_TEST_SIZE);
	if(l_sRetVal != DIR_SUCCESS)
	{
		DIR_ERRLOG("ERROR\t: Write in DDR Memory failed %hd\n", l_sRetVal);
		free(pDdrMem);
		return DIR_FAILURE;
	}

	/* Function call to read and validate DDR memory */
	l_sRetVal = readin_ddrmem(pDdrMem, DDR_TEST_SIZE);
	if(l_sRetVal != DIR_SUCCESS)
	{
		DIR_ERRLOG("ERROR\t: Read in DDR Memory failed %hd\n", l_sRetVal);
		free(pDdrMem);
		return DIR_FAILURE;
	}
	
	free(pDdrMem);
	return DIR_SUCCESS;
}

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
short writein_ddrmem(uint8_t *in_pDdrAddr, unsigned int in_uiSize)
{
	size_t l_uiLoop = DIR_INITVALUE;

	/* Validate input args */
	if(in_pDdrAddr == NULL)
	{
		DIR_ERRLOG("ERROR\t: Invalid input pointer for writein_ddrmem\n");
		return DIR_FAILURE;
	}
	if( (in_uiSize < DDR_MINSIZE) || (in_uiSize > DDR_MAXSIZE) )
	{
		DIR_ERRLOG("ERROR\t: Invalid input size for writein_ddrmem %u\n", in_uiSize);
		return DIR_FAILURE;
	}

	/* Write counter data in DDR memory */
	for(l_uiLoop = DIR_INITVALUE; l_uiLoop < in_uiSize; l_uiLoop++)
	{
		in_pDdrAddr[l_uiLoop] = (uint8_t)(l_uiLoop % 256);
	}

	return DIR_SUCCESS;
}

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
short readin_ddrmem(uint8_t *in_pDdrAddr, unsigned int in_uiSize)
{
	size_t l_uiLoop = DIR_INITVALUE;

	/* Validate input args */
	if(in_pDdrAddr == NULL)
	{
		DIR_ERRLOG("ERROR\t: Invalid input pointer for readin_ddrmem\n");
		return DIR_FAILURE;
	}
	if( (in_uiSize < DDR_MINSIZE) || (in_uiSize > DDR_MAXSIZE) )
	{
		DIR_ERRLOG("ERROR\t: Invalid input size for readin_ddrmem %u\n", in_uiSize);
		return DIR_FAILURE;
	}	

	/* Read data from DDR memory */
	for(l_uiLoop = DIR_INITVALUE; l_uiLoop < in_uiSize; l_uiLoop++)
	{
		/* Validating the data */
		if( in_pDdrAddr[l_uiLoop] != (uint8_t)(l_uiLoop % 256) )
		{
			break;
		}
	}
	if(l_uiLoop < in_uiSize)
	{
		return DIR_FAILURE;
	}

	return DIR_SUCCESS;
}
