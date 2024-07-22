#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h> // for open
#include <errno.h> // for error codes

/* Macros */
#define Driver_path        "/dev/ModuleDiagnostic"
#define DIR_SUCCESS        0
#define DIR_FAILURE        -1
#define DIR_LOG            printf         /* Macro for information messages */
#define DIR_ERRLOG         printf         /* Macro for error messages */

/* Operation codes */
#define OP_32BIT_WRITE     6

/* Structure to store memory operation details */
struct core_mem {
    unsigned int operation;
    unsigned int address;
    unsigned int value;
};

unsigned int write_operation[] = {
    0x80116000, 0x80116004, 0x80116008, 0x8011600C, 0x80116010, 0x80116014, 0x80116018, 0x8011601C, 0x80116020,
    0x80116024, 0x80116028, 0x8011602C, 0x80116030, 0x80116034, 0x80116038, 0x8011603C, 0x80116040, 0x80116044,
    0x80116048, 0x8011604C, 0x80116050, 0x80116054, 0x80116058, 0x8011605C, 0x80116060, 0x80116064, 0x80116068,
    0x8011606C, 0x80116070, 0x80116074, 0x80116078, 0x8011607C, 0x80116080, 0x80116084, 0x80116088, 0x8011608C,
    0x80116090, 0x80116094, 0x80116098, 0x8011609C, 0x801160A0, 0x801160A4, 0x801160A8, 0x801160AC, 0x801160B0,
    0x801160B4, 0x801160B8, 0x801160BC, 0x801160C0, 0x801160C4, 0x801160C8, 0x801160CC, 0x801160D0, 0x801160D4,
    0x801160D8, 0x801160DC, 0x801160E0, 0x801160E4, 0x801160E8, 0x801160EC, 0x801160F0, 0x801160F4, 0x801160F8,
    0x801160FC, 0x80116100, 0x80116104, 0x80116108, 0x8011610C, 0x80116110, 0x80116114, 0x80116118, 0x8011611C,
    0x80116120, 0x80116124, 0x80116128, 0x8011612C, 0x80116130, 0x80116134, 0x80116138, 0x8011613C, 0x80116140,
    0x80116144, 0x80116148, 0x8011614C, 0x80116150, 0x80116154, 0x80116158, 0x8011615C, 0x80116160, 0x80116164,
    0x80116168, 0x8011616C, 0x80116170, 0x80116174, 0x80116178, 0x8011617C, 0x80116180, 0x80116184, 0x80116188,
    0x8011618C, 0x80116190, 0x80116194, 0x80116198, 0x8011619C, 0x801161A0, 0x801161A4, 0x801161A8, 0x801161AC,
    0x801161B0, 0x801161B4, 0x801161B8, 0x801161BC, 0x801161C0, 0x801161C4, 0x801161C8, 0x801161CC, 0x801161D0,
    0x801161D4, 0x801161D8, 0x801161DC, 0x801161E0, 0x801161E4, 0x801161E8, 0x801161EC, 0x801161F0, 0x801161F4,
    0x801161F8, 0x801161FC, 0x80116200, 0x80116204, 0x80116208, 0x8011620C, 0x80116210, 0x80116214, 0x80116218,
    0x8011621C, 0x80116220, 0x80116224, 0x80116228, 0x8011622C, 0x80116230, 0x80116234, 0x80116238, 0x8011623C,
    0x80116240, 0x80116244, 0x80116248, 0x8011624C
};

unsigned int data_to_write[] = {
        0x8B000987, 0x00000000, 0x00000001, 0xdd9eb80c, 0x81F20000, 0x9d71ef95, 0x04000000, 0x00000001, 0x281e1ecc,
        0x001F4000, 0x9c845c42, 0x07000000, 0x00000003, 0xc5b7ac97, 0x00000000, 0x00000001, 0xE0000000, 0x17752489,
        0x0A000000, 0x00000011, 0xc737f732, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x10d76ead, 0x01000000, 0x00000001, 0xe0fe91bc, 0x00000000, 0x2144df1c, 0x02000000,
        0x00000002, 0xb5eb4482, 0x00000000, 0x47D41000, 0x74e8a831, 0x03000000, 0x00000001, 0x9a3ec2dc, 0x00020000,
        0x1372bd9e, 0x05000000, 0x00000003, 0xbf77fff7, 0x00000000, 0x00000000, 0x00000000, 0x7bd5c66f, 0x06000000,
        0x00000001, 0x52de4dac, 0x7FF7FF00, 0x049bf026, 0x08000000, 0x00000002, 0xff5b5c23, 0x0A000000, 0xE7F9FE00,
        0x6bd8b43d, 0x09000000, 0x00000001, 0xd08eda7d, 0x10000000, 0x3cf3cf78, 0x0B000000, 0x00000003, 0x00474196,
        0xFE000000, 0x06EAB6EA, 0x00208400, 0x3f73c7ee, 0x20000000, 0x00000003, 0xb6565f83, 0xBABE0000, 0x5678BAAD,
        0x00000000, 0xd3cf6092, 0x21000000, 0x00000003, 0x8b367633, 0x00000000, 0x00000000, 0x20040000, 0x24d723a3,
        0x22000000, 0x00000001, 0x669fc468, 0x00000000, 0x2144df1c, 0x23000000, 0x0000000e, 0x039cfd8e, 0x00000000,
        0x00500000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x4556de60, 0x24000000, 0x00000001, 0xe9df31c8, 0x00000000,
        0x2144df1c, 0x25000000, 0x00000002, 0xc60ab796, 0x80000000, 0x20500015, 0x32d6b5ca, 0x27000000, 0x00000001,
        0xae7f4b18, 0x00000000, 0x2144df1c, 0x29000000, 0x00000003, 0xbb463df2, 0x757C0000, 0x3C03755B, 0x0FF04010,
        0xdd4d34a5, 0x00000000, 0x00000000, 0x1942129e
};

const char *register_name[] = {
	"Device_id", "Schedule Table", "BlockLength", "crc_std", "DATA", "crc_std", "Schedule Entry Points Table", "BlockLength", 
	"crc_std", "DATA", "crc_std", "Schedule Parameters", "BlockLength", "crc_std", "DATA[31:0]", "[63:32]", "[95:64]", "crc_std", 
	"Clock Synchronization Parameter", "BlockLength", "crc_std", "DATA[31:0]", "[63:32]", "[95:64]", "[127:96]", "[159:128]", 
	"[191:160]", "[223:192]", "[255:224]", "[287:256]", "[319:288]", "[351:320]", "[383:352]", "[415:384]", "[447:416]", 
	"[479:448]", "[511:480]", "[543:512]", "crc_std", "IC/RM Table", "BlockLength", "crc_std", "DATA", "crc_std", "Output VL Table", 
	"BlockLength", "crc_std", "DATA[31:0]", "[63:32]", "crc_std", "Input VL Lookup Table", "BlockLength", "crc_std", "DATA[31:0]", 
	"crc_std", "Best-Effort Filter Table", "BlockLength", "crc_std", "DATA[31:0]", "[63:32]", "[95:64]", "crc_std", "Partition Space Table", 
	"BlockLength", "crc_std", "DATA[31:0]", "crc_std", "Shaping Parameters", "BlockLength", "crc_std", "DATA[31:0]", "[63:32]", "crc_std", 
	"IC/RM Parameters", "BlockLength", "crc_std", "DATA[31:0]", "crc_std", "General Parameters", "BlockLength", "crc_std", "DATA[31:0]", "[63:32]", 
	"[95:64]", "crc_std", "Output Parameters", "BlockLength", "crc_std", "DATA[31:0]", "[63:32]", "[95:64]", "crc_std", "Output Port Table",
	"BlockLength", "crc_std", "DATA[31:0]", "[63:32]", "[95:64]", "crc_std", "Output Partition Table", "BlockLength", "crc_std", "DATA[31:0]", "crc_std",
	"Input Parameters", "BlockLength", "crc_std", "DATA[31:0]", "[63:32]", "[95:64]", "[127:96]", "[159:128]", "[191:160]", "[223:192]", "[255:224]",
	"[287:256]", "[319:288]", "[351:320]", "[383:352]", "[415:384]", "[447:416]", "crc_std", "Input Lookup Table", "BlockLength", "crc_std", "DATA[31:0]", 
	"crc_std", "Input Port Table", "BlockLength", "crc_std", "DATA[31:0]", "[63:32]", "crc_std", "Input Defragmentation Table", "BlockLength", "crc_std", 
	"DATA[31:0]", "crc_std", "Output Sub-VL Table", "BlockLength", "crc_std", "DATA[31:0]", "[63:32]", "[95:64]", "crc_std", "block id 0", 
	"eof file(block length zero)", "koopman crc"
};

/* Function declaration */
int core_configuration_main(void);
