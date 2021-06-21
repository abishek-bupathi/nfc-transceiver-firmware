#include "mbed.h"
#include "pn532.h"
#include <cstdint>
#include <cstdio>

PN532::PN532(PinName i2c_sda, PinName i2c_scl):i2c(i2c_sda, i2c_scl){
    init();
}

void PN532::init(void){
    i2c.frequency(400000);
}

uint32_t PN532::get_firmware_version(void){

    char cmd[1];
    cmd[0] = PN532_CMD_GET_FIRMWARE_VERSION;
    uint32_t fw_ver;

    uint8_t ack = i2c_write_cmd(cmd, sizeof(cmd));

    char response[12];

    i2c_read_response(response, sizeof(response));

    // Checking data frame info for fw version
    for(int i=0; i < 6; i++){
        if(response[i] != FW_VER_FRAME[i]){
            return 0xDEADBEEF;
        }
    }

    int offset = 7;
    fw_ver = response[offset++];
    fw_ver <<= 8;
    fw_ver |= response[offset++];
    fw_ver <<= 8;
    fw_ver |= response[offset++];
    fw_ver <<= 8;
    fw_ver |= response[offset++];

    return fw_ver;
}

uint8_t PN532::get_target_id(void){
    return 1;
}

uint8_t PN532::read_iso14443A(uint8_t data){
    return 1;
}

uint8_t PN532::write_iso14443A(uint8_t data){

    return 1;
}

uint8_t PN532::read_ntag(uint8_t data){

    return 1;
}

uint8_t PN532::write_ntag(uint8_t data){

    return 1;
}

uint8_t PN532::read_mifare_classic(uint8_t data){

    return 1;
}

uint8_t PN532::write_mifare_classic(uint8_t data){

    return 1;
}

uint8_t PN532::read_mifare_ultralight(uint8_t data){

    return 1;
}

uint8_t PN532::write_mifare_ultralight(uint8_t data){

    return 1;
}

int PN532::i2c_write_cmd(char *cmd, uint8_t cmd_len){

    char packet[8+cmd_len];
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
            packet[6+i] = cmd[i];
            sum += cmd[i];
        }
    }

    packet[packet_len - 2] = ~sum + 1; // Checksun of data
    packet[packet_len - 1] = PN532_POSTAMBLE;

    printf("\n\nWrite: ");
    for(int i = 0; i < packet_len; i++){
        printf("%x ", packet[i]);
    }

    i2c.write(PN532_I2C_ADDR, packet, packet_len);

    return check_ack();
}

int PN532::i2c_read_response(char *packet, uint8_t packet_len){

    packet_len++;

    while (is_device_ready() != 0x01){
        wait_us(1000);
    }

    i2c.read(PN532_I2C_ADDR, packet, packet_len);
    
    printf("\n\nRead: ");

    for(int i = 1; i < packet_len; i++){
        printf("%x ", packet[i]);
        packet[i-1] = packet[i];
    }

    return 1;
}

bool PN532::check_ack(void){
    
    char ack_response[7];
    bool ack_valid = true;

    while (is_device_ready() != 0x01){
        wait_us(100);
    }
   
    i2c.read(PN532_I2C_ADDR, ack_response, sizeof(ack_response));

    for(int i = 1; i < sizeof(ack_response); i++){
        if(ack_response[i] != ACK_FRAME[i-1]){
            ack_valid = false;
        }
    }

    return ack_valid;
}

bool PN532::is_device_ready(void){

    char rdy[0];
    
    i2c.read(PN532_I2C_ADDR, rdy, 1);
    
    return rdy[0] & 0x1; 
} 
