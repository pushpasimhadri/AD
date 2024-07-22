/****************************************************************************
 * @file:        registers.c
 * 
 * @Created:     02-05-2024
 *
 * @brief:       To access any register mapped via I/O range or CPU Range.
 *               This can be cross compiled for any arch.
 *        
 * @Version:     1.0
 *
 * @Author:      Capgemini Engineering    
 **************************************************************************/

#include "registers.h"

/*Interface struct between driver and application, user configurable*/
struct mem {
	unsigned int operation;
	unsigned int address;
	unsigned int value;
};

/*Function name:
 *    registers_main - This function perform 8,16,32 bit write and read operations on the registers.
 *
 *Parameters:
 *    None
 *
 *Return Value:
 *      DIR_SUCCESS - If the data read/write successfully, function will return DIR_SUCCESS
 *      DIR_FAILURE - If the driver failed to open, unable to perform read/write operations, it will return DIR_FAILURE
 */
int registers_main(void)
{
    int l_hFile; /* File descriptor for the device driver */
    uint32_t l_result;
    struct mem s_obj_mem; /* Structure to store memory operation details */

        /* Open the device driver path */
	l_hFile = open(Driver_path, O_WRONLY);
	
	/* Check if the device driver was opened successfully */
	if(l_hFile == -1)
	{
		DIR_ERRLOG("open failed for %s\n", Driver_path);
		return DIR_FAILURE;
	}
	DIR_LOG("Opening /dev/ModuleDiagnostic ");

	s_obj_mem.operation = 0;

		/* Display menu options for FPGA read/write operations */
		printf("Entering into FPGA read/write\n");
                printf("1. 8 BIT Read\n");
                printf("2. 16 BIT Read\n");
                printf("3. 32 BIT Read\n");
                printf("4. 8 BIT Write\n");
                printf("5. 16 BIT Write\n");
                printf("6. 32 BIT Write\n");
                printf(" Pass Operation Code \n");
                scanf("%d", &s_obj_mem.operation);

                switch(s_obj_mem.operation) {
			case 1:
				printf(" 8 bit Read Selected \n");
				printf(" Pass Address \n");
				/* Read address from user */
				scanf("%x", &s_obj_mem.address);
				break;
			case 2:
				printf(" 16 bit Read Selected \n");
				printf(" Pass Address \n");
				/* Read address from user */
				scanf("%x", &s_obj_mem.address);
				break;
			case 3:
				printf(" 32 bit Read Selected \n");
				printf(" Pass Address \n");
				/* Read address from user */
				scanf("%x", &s_obj_mem.address);
				break;
			case 4:
				printf(" 8 bit Write Selected \n");
				printf(" Pass Address \n");
				/* Read address from user */
				scanf("%x", &s_obj_mem.address);
				printf(" Pass Value \n");
				/* Read value to write from user */
				scanf("%x", &s_obj_mem.value);
				break;
			case 5:
				printf(" 16 bit Write Selected \n");
				printf(" Pass Address \n");
				/* Read address from user */
				scanf("%x", &s_obj_mem.address);
				printf(" Pass Value \n");
				/* Read value to write from user */
				scanf("%x", &s_obj_mem.value);
				break;
			case 6:
				printf(" 32 bit Write Selected \n");
				printf(" Pass Address \n");
				/* Read address from user */
				scanf("%x", &s_obj_mem.address);
				printf(" Pass Value \n");
				/* Read value to write from user */
				scanf("%x", &s_obj_mem.value);
				break;
			default:
				printf(" Wrong entry, pls try example if you want to do \n");
				printf(" 16 bit word read, your input should be 14 \n");
				printf(" Here (1) for Read & (4) for Word \n");
		}
		
		l_result = ioctl(l_hFile,0,&s_obj_mem);
		if( (s_obj_mem.operation == 1) || (s_obj_mem.operation == 2) || (s_obj_mem.operation == 3) )
		{
			DIR_LOG("INFO:\t Register: %08X Value: %08X\n", s_obj_mem.address, l_result);
		}
		/* Close the device driver file */
		close(l_hFile);
		return DIR_SUCCESS;
}
