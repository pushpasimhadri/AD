#include "can_registers.h"

/* Operations array */
struct mem operations[] = {
    {0x85001000, 0xB0005127, OP_32BIT_WRITE}, {0x85002000, 0xB0005127, OP_32BIT_WRITE},
    {0x85000000, 0x00000000, OP_32BIT_WRITE}, {0x85002004, 0x00000123, OP_32BIT_WRITE},
    {0x85002008, 0x00000123, OP_32BIT_WRITE}, {0x85001020, 0x00000123, OP_32BIT_WRITE},
    {0x85001024, 0x00000000, OP_32BIT_WRITE}, {0x85001028, 0x0000000F, OP_32BIT_WRITE},
    {0x8500102C, 0x00000104, OP_32BIT_WRITE}, {0x85001018, OP_32BIT_READ},
    {0x85002018, OP_32BIT_READ}, {0x85000008, OP_32BIT_READ}, {0x85000014, OP_32BIT_READ},
    {0x85000004, 0x00000004, OP_32BIT_WRITE}, {0x85000008, OP_32BIT_READ},
    {0x85000004, 0x00000000, OP_32BIT_WRITE}, {0x8500200C, OP_32BIT_READ},
    {0x8500201C, OP_32BIT_READ}, {0x8500201C, OP_32BIT_READ}, {0x8500201C, OP_32BIT_READ},
    {0x8500201C, OP_32BIT_READ}, {0x85001014, OP_32BIT_READ}, {0x85002014, OP_32BIT_READ},
    {0x8500200C, OP_32BIT_READ}
};

#define NUM_OPERATIONS (sizeof(operations) / sizeof(operations[0]))

/* Function: reg_main
 * ------------------------
 * This function performs the sequence of 32-bit read and write operations on the registers.
 *
 * Parameters:
 *    None
 *
 * Return Value:
 *    DIR_SUCCESS - If the data is read/written successfully, the function will return DIR_SUCCESS.
 *    DIR_FAILURE - If the driver failed to open or unable to perform read/write operations, it will return DIR_FAILURE.
 */
int can_main(void) {
    int l_hFile;         /* File descriptor for the device driver */
    int l_result;

    /* Open the device driver path */
    l_hFile = open(Driver_path, O_WRONLY);

    /* Check if the device driver was opened successfully */
    if (l_hFile == -1) {
        perror("open failed for /dev/ModuleDiagnostic");
        return DIR_FAILURE;
    }
    printf("Opened /dev/ModuleDiagnostic\n");

    /* Perform the operations in sequence */
    for (size_t i = 0; i < NUM_OPERATIONS; i++) {
        if (operations[i].operation == OP_32BIT_WRITE) {
            l_result = ioctl(l_hFile, 0, &operations[i]);
            if (l_result == -1) {
                perror("32-bit write failed");
                printf("32-bit write failed for address 0x%08X\n", operations[i].address);
                close(l_hFile);
                return DIR_FAILURE;
            }
            printf("32-bit Write: Address: 0x%08X written value: 0x%08X\n", operations[i].address, operations[i].value);
        } else {
            l_result = ioctl(l_hFile, 0, &operations[i]);
            if (l_result == -1) {
                perror("32-bit read failed");
                printf("32-bit read failed for address 0x%08X\n", operations[i].address);
                close(l_hFile);
                return DIR_FAILURE;
            }
            printf("32-bit Read: Address: 0x%08X Value: 0x%08X\n", operations[i].address, operations[i].value);
        }
    }

    /* Close the device driver file */
    close(l_hFile);
    return DIR_SUCCESS;
}
