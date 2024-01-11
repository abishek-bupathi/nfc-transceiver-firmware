#include "mbed.h"
#include "PN532.h"
#include <cstdint>

PN532::PN532(PinName i2c_sda, PinName i2c_scl):i2c(i2c_sda, i2c_scl){
    init();
}

void PN532::init(void){
    i2c.frequency(100000);
}

uint8_t PN532::get_firmware_version(void){

}

uint8_t PN532::get_target_id(void){

}

uint8_t PN532::read_iso14443A(uint8_t data){

}

uint8_t PN532::write_iso14443A(uint8_t data){

}

uint8_t PN532::read_ntag(uint8_t data){

}

uint8_t PN532::write_ntag(uint8_t data){

}

uint8_t PN532::read_mifare_classic(uint8_t data){

}

uint8_t PN532::write_mifare_classic(uint8_t data){

}

uint8_t PN532::read_mifare_ultralight(uint8_t data){

}

uint8_t PN532::write_mifare_ultralight(uint8_t data){

}

int i2c_write_cmd(I2C i2c, uint8_t *cmd, uint8_t cmd_len){

    char packet[64];
    uint8_t sum;

    uint8_t data_len = cmd_len + 1; // Command + TFI length
    uint8_t packet_len = cmd_len + 8; // Total packet length

    packet[0] = PN532_PREAMBLE;
    packet[1] = PN532_START_CODE_1;
    packet[2] = PN532_START_CODE_2;
    packet[3] = data_len;   
    packet[4] = ~data_len + 1; // Checksum of length
    packet[5] = PN532_TFI_HOST_TO_PN532;

    sum = PN532_TFI_HOST_TO_PN532;

    if(cmd_len <= 54){
        for(int i = 0; i < cmd_len; i++){
            packet[5+i] = cmd[i];
            sum += cmd[i];
        }
    }

    packet[packet_len - 2] = ~sum + 1; // Checksun of data
    packet[packet_len - 1] = PN532_POSTAMBLE;

    i2c.write(PN532_I2C_ADDR, packet, packet_len);
    
    return i2c.ACK;
}

int i2c_read_response(uint8_t *command){


}

bool is_device_read(void){

}