/****************************************************************************
 * @file:        AFDX_registers.c
 * 
 * @Created:     08-07-2024
 *
 * @brief:       To access any register mapped via I/O range or CPU Range.
 *               This can be cross compiled for any arch.
 *        
 * @Version:     1.0
 *
 * @Author:      Capgemini Engineering    
 **************************************************************************/
#include "AFDX_registers.h"

unsigned int read_operation_32[] = {
    0x80100000, 0x80100004, 0x80100008, 0x8010000C, 0x80100010, 0x80100014, 0x80100018, 0x8010001C,
    0x80100020, 0x80100024, 0x80100028, 0x8010002C, 0x80100030, 0x80100034, 0x80100038, 0x8010003C,
    0x80100040, 0x80100044, 0x80100048, 0x8010004C, 0x80100050, 0x80100054, 0x80100058, 0x8010005C
};

const char *register_names[] = {
    "ES_IF_APB_L", "ES_IF_APB_H", "PHY_SCU_L", "PHY_SCU_H", "MDIO_0_L", "MDIO_0_H", "MDIO_1_L", "MDIO_1_H",
    "MDIO_2_L", "MDIO_2_H", "ES_RSCU_L", "ES_RSCU_H", "ES_BIST_L", "ES_BIST_H", "ES_PIN_MUX_L", "ES_PIN_MUX_H",
    "ES_IP_VER_L", "ES_IP_VER_H", "ES_CORE_APB_L", "ES_CORE_APB_H", "ES_CORE_AXI_L", "ES_CORE_AXI_H", "END_OF_LIST_L",
    "END_OF_LIST_H"
};

#define NUM_READ_32  (sizeof(read_operation_32) / sizeof(read_operation_32[0]))

/* Function: AFDX_main
 * ------------------------
 * This function performs the fixed 32-bit read operation on the registers.
 *
 * Parameters:
 *    None
 *
 * Return Value:
 *    DIR_SUCCESS - If the data is read successfully, the function will return DIR_SUCCESS.
 *    DIR_FAILURE - If the driver failed to open or unable to perform read operation, it will return DIR_FAILURE.
 */
int AFDX_main(void) {
    int l_hFile;         /* File descriptor for the device driver */
    uint32_t l_result;
    struct AFDX_mem s_obj_mem; /* Structure to store memory operation details */

    /* Open the device driver path */
    l_hFile = open(Driver_path, O_RDONLY);

    /* Check if the device driver was opened successfully */
    if (l_hFile == -1) {
        DIR_ERRLOG("open failed for %s\n", Driver_path);
        return DIR_FAILURE;
    }
    DIR_LOG("Opened /dev/ModuleDiagnostic\n");

    for (size_t i = 0; i < NUM_READ_32; i++) {
        s_obj_mem.operation = OP_32BIT_READ; // 32-bit read operation
        s_obj_mem.address = read_operation_32[i];
        l_result = ioctl(l_hFile, 0, &s_obj_mem);
        if (l_result == -1) {
            DIR_ERRLOG("32-bit read failed for address %X\n", s_obj_mem.address);
            close(l_hFile);
            return DIR_FAILURE;
        }
        
        // Ensure i is within bounds of register_names array
        if (i < sizeof(register_names) / sizeof(register_names[0])) {
            DIR_LOG("INFO:\t %s\t Register: 0X%08X  Value: %08X\n", register_names[i], s_obj_mem.address, l_result);
        } else {
            DIR_LOG("INFO:\t Register: 0x%08X Value: %08X\n", s_obj_mem.address, l_result);
        }
    }

    /* Close the device driver file */
    close(l_hFile);
    return DIR_SUCCESS;
}
