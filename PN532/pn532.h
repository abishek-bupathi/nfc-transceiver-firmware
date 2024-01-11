#include "mbed.h"
#include <cstdint>

/**************** Pin definitions ****************/
#define I2C_SDA_PIN                         D4
#define I2C_SCL_PIN                         D5              


/******************* Commands ********************/

// General 
#define PN532_CMD_DIAGNOSE                  0x00
#define PN532_CMD_GET_FIRMWARE_VERSION      0x02
#define PN532_CMD_GET_GENERAL_STATUS        0x04
#define PN532_CMD_READ_REGISTER             0x06
#define PN532_CMD_WRITE_REGISTER            0x08
#define PN532_CMD_READ_GPIO                 0x0C
#define PN532_CMD_WRITE_GPIO                0x0E
#define PN532_CMD_SET_SERIAL_BAUD_RATE      0x10
#define PN532_CMD_SET_PARAMETERS            0x12
#define PN532_CMD_SAM_CONFIGURATION         0x14
#define PN532_CMD_POWER_DOWN                0x16

// RF
#define PN532_CMD_RF_CONFIGURATION          0x32
#define PN532_CMD_RF_REGULATION_TEST        0x58

// Initiator
#define PN532_CMD_IN_JUMP_FOR_DEP           0x56    
#define PN532_CMD_IN_JUMP_FOR_PSL           0x46
#define PN532_CMD_IN_LIST_PASSIVE_TARGET    0x4A
#define PN532_CMD_IN_ATR                    0x50
#define PN532_CMD_IN_PSL                    0x4E
#define PN532_CMD_IN_DATA_EXCHANGE          0x40    
#define PN532_CMD_IN_COMMUNICATE_THRU       0x42
#define PN532_CMD_IN_DESELECT               0x44
#define PN532_CMD_IN_RELEASE                0x52
#define PN532_CMD_IN_SELECT                 0x54
#define PN532_CMD_IN_AUTO_POLL              0x60


/******************* Address ********************/
#define PN532_I2C_ADDR                      0x48


/****************** Constants *******************/
#define PN532_PREAMBLE                      0x00
#define PN532_POSTABLE                      0x00

#define PN532_START_CODE_1                  0x00
#define PN532_START_CODE_2                  0xFF

#define PN532_TFI_HOST_TO_PN532             0xD4
#define PN532_TFI_PN532_TO_HOST             0xD5


class PN532{

    public:

    PN532(PinName i2c_sda,PinName i2c_scl);

    void init();

    // NFC functions
    uint8_t get_firmware_version(void);
    uint8_t get_target_id(void);
    uint8_t read_iso14443A(uint8_t data);
    uint8_t write_iso14443A(uint8_t data);
    uint8_t read_ntag(uint8_t data);
    uint8_t write_ntag(uint8_t data);
    uint8_t read_mifare_classic(uint8_t data);
    uint8_t write_mifare_classic(uint8_t data);
    uint8_t read_mifare_ultralight(uint8_t data);
    uint8_t write_mifare_ultralight(uint8_t data);

    private:

    I2C i2c;

    // I2C functions
    int i2c_write(uint8_t data);
    int i2c_read(uint8_t command);
    bool is_device_read(void);
    
};


