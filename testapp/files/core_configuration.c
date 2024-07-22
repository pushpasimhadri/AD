#include "core_configuration.h"

#define NUM_WRITE (sizeof(write_operation) / sizeof(write_operation[0]))

/* Function: Core_configuration_main
 * ------------------------
 * This function performs the fixed 32-bit read and write operations on the registers.
 *
 * Parameters:
 *    None
 *
 * Return Value:
 *    DIR_SUCCESS - If the data is read/written successfully, the function will return DIR_SUCCESS.
 *    DIR_FAILURE - If the driver failed to open or unable to perform read/write operations, it will return DIR_FAILURE.
 */
int core_configuration_main(void) {
    int l_hFile;         /* File descriptor for the device driver */
    int l_result;
    struct core_mem s_obj_mem; /* Structure to store memory operation details */

    /* Open the device driver path */
    l_hFile = open(Driver_path, O_WRONLY);

    /* Check if the device driver was opened successfully */
    if (l_hFile == -1) {
        printf("open failed for %s\n", Driver_path);
        return DIR_FAILURE;
    }
    printf("Opened /dev/ModuleDiagnostic\n");

    /* Perform 32-bit write operations */
    for (size_t i = 0; i < NUM_WRITE; i++) {
        s_obj_mem.operation = OP_32BIT_WRITE; // 32-bit write operation
        s_obj_mem.address = write_operation[i];
        s_obj_mem.value = data_to_write[i];
        l_result = ioctl(l_hFile, 0, &s_obj_mem);
        if (l_result == -1) {
            printf("32-bit write failed for address %X\n", s_obj_mem.address);
            close(l_hFile);
            return DIR_FAILURE;
        }

    // Ensure i is within bounds of register_name array
        if (i < sizeof(register_name) / sizeof(register_name[0])) {
            DIR_LOG("INFO:\t %s\t Register: 0X%08X  Written Value: %08X\n", register_name[i], s_obj_mem.address, s_obj_mem.value);
        } else {
            DIR_LOG("INFO:\t Register: 0x%08X Value: %08X\n", s_obj_mem.address, l_result);
        }
    }

    /* Close the device driver file */
    close(l_hFile);
    return DIR_SUCCESS;
}
