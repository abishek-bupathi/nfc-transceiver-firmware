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

    // Initialise the digital pin LED1 as an outputs
    //DigitalOut led(LED1);s
   
    //while (true) {
    //    led = !led;
    //   ThisThread::sleep_for(500ms);   
    //}

    
}

