#include "mbed.h"
#include "pn532.h"
#include <cstdio>

PN532 nfc_tag(I2C_SDA_PIN, I2C_SCL_PIN);

// main() runs in its own thread in the OS
int main()
{

    uint32_t fw_ver = nfc_tag.get_firmware_version();
    printf("\n\n");
    printf("Found chip: PN5%x\n", (fw_ver>>24) & 0xFF);
    printf("Firmware version: %d.%d", (fw_ver>>16) & 0xFF, (fw_ver>>8) & 0xFF);
    
    uint8_t ack;

    //uint8_t ack = nfc_tag.set_sam_mode(PN532_SAM_MODE_NORMAL);

    //ack = nfc_tag.enable_rf_field();

   
    //genStatus_t status = nfc_tag.get_general_status();

    uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
    uint8_t uidLength;

    
    ack = nfc_tag.get_target_id(PN532_MIFARE_ISO14443A, uid, &uidLength);

    char data[] = "123";

    nfc_tag.in_exchange_data(0x1, data, sizeof(data));
}
    

