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
#define PN532_POSTAMBLE                     0x00

#define PN532_START_CODE_1                  0x00
#define PN532_START_CODE_2                  0xFF

#define PN532_TFI_HOST_TO_PN532             0xD4
#define PN532_TFI_PN532_TO_HOST             0xD5

#define PN532_RF_FIELD_ITEM                 0x01
#define PN532_RF_FIELD_ENABLE               0x01

#define PN532_SAM_MODE_NORMAL               0x01
#define PN532_SAM_TIMEOUT                   0xFF
#define PN532_SAM_IRQ                       0x01

#define PN532_MIFARE_ISO14443A              0x00

const uint8_t ACK_FRAME[6] = {0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00};
const uint8_t FW_VER_FRAME[6] = {0x00, 0x00, 0xFF, 0x06, 0xFA, 0xD5};

typedef struct{
        uint8_t mErr;
        uint8_t mField;
        uint8_t mNbTg;
        uint8_t mTg1;
        uint8_t mBrRx1;
        uint8_t mBrTx1;
        uint8_t mType1;
        uint8_t mTg2;
        uint8_t mBrRx2;
        uint8_t mBrTx2;
        uint8_t mType2;
        uint8_t mSam;
} genStatus_t;

class PN532{

    public:


    PN532(PinName i2c_sda,PinName i2c_scl);

    void init();

    // NFC functions
    uint32_t get_firmware_version(void);

    uint8_t get_target_id(uint8_t baudRate, uint8_t* uid, uint8_t* uidLength);
    uint8_t set_sam_mode(uint8_t mode);
    uint8_t enable_rf_field(void);
    uint8_t get_target_type(void);
    genStatus_t get_general_status(void);
    uint8_t in_exchange_data(uint8_t targetNo, char* data, uint8_t dataLen);
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
    int i2c_write_cmd(char *cmd, uint8_t cmd_len);
    int i2c_read_response(char *packet, uint8_t packet_len);
    bool check_ack(void);
    bool is_device_ready(void);

};


