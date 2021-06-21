#include "mbed.h"
#include <cstdint>

/************* Pin definitions *************/
#define I2C_SDA_PIN                      D4
#define I2C_SCL_PIN                      D5              


/**************** Commands *****************/

// General 
#define DIAGNOSE                        0x00
#define GET_FIRMWARE_VERSION            0x02
#define GET_GENERAL_STATUS              0x04
#define READ_REGISTER                   0x06
#define WRITE_REGISTER                  0x08
#define READ_GPIO                       0x0C
#define WRITE_GPIO                      0x0E
#define SET_SERIAL_BAUD_RATE            0x10
#define SET_PARAMETERS                  0x12
#define SAM_CONFIGURATION               0x14
#define POWER_DOWN                      0x16

// RF
#define RF_CONFIGURATION                0x32
#define RF_REGULATION_TEST              0x58

// Initiator
#define IN_JUMP_FOR_DEP                 0x56    
#define IN_JUMP_FOR_PSL                 0x46
#define IN_LIST_PASSIVE_TARGET          0x4A
#define IN_ATR                          0x50
#define IN_PSL                          0x4E
#define IN_DATA_EXCHANGE                0x40    
#define IN_COMMUNICATE_THRU             0x42
#define IN_DESELECT                     0x44
#define IN_RELEASE                      0x52
#define IN_SELECT                       0x54
#define IN_AUTO_POLL                    0x60

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


