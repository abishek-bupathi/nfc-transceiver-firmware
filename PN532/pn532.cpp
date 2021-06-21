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

    uint8_t packet[8];

    packet[0] = PN532_PREAMBLE;
    packet[0] = 

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


uint8_t PN532::write_cmd(){

}

int i2c_write(uint8_t data){

}

int i2c_read(uint8_t *command){


}

bool is_device_read(void){

}