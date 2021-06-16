#include "mbed.h"

/********* Commands *********/

// General 
#define DIAGNOSE                    0x00
#define GET_FIRMWARE_VERSION        0x02
#define GET_GENERAL_STATUS          0x04
#define READ_REGISTER               0x06
#define WRITE_REGISTER              0x08
#define READ_GPIO                   0x0C
#define WRITE_GPIO                  0x0E
#define SET_SERIAL_BAUD_RATE        0x10
#define SET_PARAMETERS              0x12
#define SAM_CONFIGURATION           0x14
#define POWER_DOWN                  0x16

// RF
#define RF_CONFIGURATION            0x32
#define RF_REGULATION_TEST          0x32
