/*****************************************************
 *  CAP1188-WLS Raw Data Demo
 *  File:   CAP1188-WLS.ino
 *  Date:   2016_05_06
 *  Author: Stephen Minakian
 *  Version:0.0.1
 *
 *  Description:
 *    This application sets up the CA1188 with WLS
 *    settings and displays the raw delta count for
 *    each segment.
 *****************************************************/

#include "CAP1188.h"

Cap1188_touch waterLevelSensor;

void setup() {
    Serial1.begin(115200);
    Serial1.print("\r\nParticle has started.\r\n");
    pinMode(D7, OUTPUT);
    waterLevelSensor.begin();
    delay(100);
    
    Serial1.printf("Device info 0x%08x\r\n", waterLevelSensor.getDeviceInfo());
    
    waterLevelSensor.writeRegister(CAP1188_REG_MAIN_CONTROL, 0);
    waterLevelSensor.writeRegister(CAP1188_REG_SENSITIVITY_CONTROL, 0x6F);
    waterLevelSensor.writeRegister(CAP1188_REG_CONFIGURATION, 0xB0);
    waterLevelSensor.writeRegister(CAP1188_REG_AVG_AND_SAMPLE_CONFIG, 0x48);
    waterLevelSensor.writeRegister(CAP1188_REG_MULTIPLE_TOUCH_CONFIG, 0x00);
    waterLevelSensor.writeRegister(CAP1188_REG_RECALIBRATION_CONFIG, 0x9F);
    waterLevelSensor.writeRegister(CAP1188_REG_SENSOR_INPUT_1_THRESHOLD, 0x1E);
    waterLevelSensor.writeRegister(CAP1188_REG_CONFIGURATION_2, 0x44);

    delay(1000);

}

void loop() {
    digitalWrite(D7, 1);
    delay(500);
    digitalWrite(D7, 0);
    delay(500);
    char i;
    for(i = 0;i<8;i++){
        char data = waterLevelSensor.readRegister(CAP1188_REG_SENSOR_INPUT_1_DELTA+i);
        if((data&0x80)!=0){
            data = (~data) + 1;
            if(data < 100){
                Serial1.printf("-%i  \t", data);
            } else {
                Serial1.printf("-%i\t", data);
            }
        } else {
            if(data < 100){
                Serial1.printf("%i  \t", data);
            } else {
                Serial1.printf("%i\t", data);
            }
        }
    }
    Serial1.print("\r");
}