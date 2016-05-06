/*****************************************************
 *  Microchip CAP1188 Library
 *  File:   CAP1188.h
 *  Date:   2016_05_05
 *  Author: Stephen Minakian
 *  Version:0.0.1
 *****************************************************/

#include "CAP1188.h"

Cap1188_touch::Cap1188_touch(){

}

bool Cap1188_touch::begin(void){
    //setAddress(CAP1188_DEFAULT_ADDRESS);
    if(Wire.isEnabled() == false){
        Wire.begin();
    }
    return true;
}

bool Cap1188_touch::begin(uint8_t newAddress){
    setAddress(newAddress);
    if(Wire.isEnabled() == false){
        Wire.begin();
    }
    return true;
}

uint32_t Cap1188_touch::getDeviceInfo(void){
    uint32_t data;

    data = getProductID();
    data <<= 8;
    data |= getMFGID();
    data <<= 8;
    data |= getRevision();
    data <<= 8;
    data |= getVendorID();

    return data;

}

uint8_t Cap1188_touch::getProductID(void){
    return readRegister(CAP1188_REG_PRODUCT_ID);
}
uint8_t Cap1188_touch::getMFGID(void){
    return readRegister(CAP1188_REG_MANUFACTURER_ID);
}
uint8_t Cap1188_touch::getRevision(void){
    return readRegister(CAP1188_REG_REVISION);
}
//uint8_t Cap1188_touch::getVendorID(void){
//    return readRegister(CAP1188_REG_VENDOR_ID);
//}

uint8_t Cap1188_touch::getAddress(void){
    return address;
}

void Cap1188_touch::setAddress(uint8_t newAddress){
    address = newAddress;
}

uint8_t Cap1188_touch::readRegister(uint8_t reg_address){
    uint8_t data;

    Wire.beginTransmission(address);
    Wire.write(reg_address);
    Wire.endTransmission();

    Wire.requestFrom(address, 1);
    data = Wire.read();

    return data;
}

void Cap1188_touch::writeRegister(uint8_t reg_address, uint8_t data){
    Wire.beginTransmission(address);
    Wire.write(reg_address);
    Wire.write(data);
    Wire.endTransmission();
}
