/****************************************************************************
 * @file:        crc_core.c
 * 
 * @Created:     18-07-2024
 *
 * @brief:       To file implements to calculate CRC for the Data and Block_Id,
 * 		 Block_length.
 *        
 * @Version:     1.0
 *
 * @Author:      Capgemini Engineering    
 **************************************************************************/
#include "crc_core.h"

// Function to reflect bits
uint32_t reflect(uint32_t data, int bits) {
    uint32_t reflection = 0;
    for (int bit = 0; bit < bits; ++bit) {
        if (data & 1) {
            reflection |= (1 << ((bits - 1) - bit));
        }
        data = (data >> 1);
    }
    return reflection;
}

// Function to calculate CRC
uint32_t calculate_crc(uint32_t *data, int length) {
    uint32_t crc = 0xFFFFFFFF;
    for (int j = 0; j < length; j++) {
        uint32_t block = reflect(data[j], 32);
        for (int i = 0; i < 32; i++) {
            uint32_t bit = (block >> (31 - i)) & 1;
            uint32_t c = (crc >> 31) & 1;
            crc <<= 1;
            if (c ^ bit) {
                crc ^= POLYNOMIAL;
            }
        }
    }
    crc = reflect(crc, 32);
    return crc ^ 0xFFFFFFFF;
}

// Function to handle CRC calculation for Block ID and Block Length
int crc_block_id_length() {
    uint32_t block_id, block_length;

    // Get Block ID and Block Length from the user
    DIR_LOG("Enter Block ID in hex format: ");
    if (scanf("%x", &block_id) != 1) {
        DIR_ERRLOG("Invalid input for Block ID\n");
        return DIR_FAILURE;
    }

    DIR_LOG("Enter Block Length in hex format: ");
    if (scanf("%x", &block_length) != 1) {
        DIR_ERRLOG("Invalid input for Block Length\n");
        return DIR_FAILURE;
    }

    // Calculate CRC for Block ID and Block Length
    uint32_t crc_id_length_data[2];
    crc_id_length_data[0] = block_id;
    crc_id_length_data[1] = block_length;
    uint32_t crc_id_length = calculate_crc(crc_id_length_data, 2);

    // Output CRC result
    DIR_LOG("CRC for Block ID and Block Length: %08X\n", crc_id_length);

    return DIR_SUCCESS;
}

// Function to handle CRC calculation for Data Blocks
int crc_data_blocks() {
    int num_data_blocks;

    // Get number of data blocks
    DIR_LOG("Enter number of data blocks: ");
    if (scanf("%d", &num_data_blocks) != 1) {
        DIR_ERRLOG("Invalid input for number of data blocks\n");
        return DIR_FAILURE;
    }

    uint32_t *data_blocks = (uint32_t *)malloc(num_data_blocks * sizeof(uint32_t));
    if (!data_blocks) {
        DIR_ERRLOG("Memory allocation failed\n");
        return DIR_FAILURE;
    }

    for (int i = 0; i < num_data_blocks; i++) {
        DIR_LOG("Enter data block %d in hex format: ", i + 1);
        if (scanf("%x", &data_blocks[i]) != 1) {
            DIR_ERRLOG("Invalid input for data block %d\n", i + 1);
            free(data_blocks);
            return DIR_FAILURE;
        }
    }

    // Calculate CRC for data blocks
    uint32_t crc_data = calculate_crc(data_blocks, num_data_blocks);
    free(data_blocks);

    // Output CRC result
    DIR_LOG("CRC for Data Blocks: %08X\n", crc_data);

    return DIR_SUCCESS;
}

/*Function name:
 *    crc_main - This function implements to calculate crc.
 *
 *Parameters:
 *    None
 *
 *Return Value:
 *      DIR_SUCCESS - If the crc for the data and Block Id, Block length calculated successfully, function will return DIR_SUCCESS
 *      DIR_FAILURE - If the entered data is invalid, it will return DIR_FAILURE
 */
int crc_main() {
    int choice;
    int status;

    // Display menu
    DIR_LOG("Select an option:\n");
    DIR_LOG("1. Calculate CRC for Block ID and Block Length\n");
    DIR_LOG("2. Calculate CRC for Data Blocks\n");
    DIR_LOG("Enter your choice (1 or 2): ");
    if (scanf("%d", &choice) != 1) {
        DIR_ERRLOG("Invalid input for choice\n");
        return DIR_FAILURE;
    }

    switch (choice) {
        case 1:
            status = crc_block_id_length();
            break;
        case 2:
            status = crc_data_blocks();
            break;
        default:
            DIR_ERRLOG("Invalid choice\n");
            return DIR_FAILURE;
    }

    return status;
}

