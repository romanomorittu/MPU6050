#include<Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial mySer(5, 6); // RX, TX
const int MPU=0x68; // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
void setup(){
Wire.begin();
Wire.beginTransmission(MPU);
Wire.write(0x6B); // PWR_MGMT_1 register
Wire.write(0); // set to zero (wakes up the MPU-6050)
Wire.endTransmission(true);
pinMode(7,INPUT);
mySer.begin(9600);
Serial.begin(9600);
}
void loop(){
Wire.beginTransmission(MPU);
Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
Wire.endTransmission(false);
Wire.requestFrom(MPU,14,true); // request a total of 14 registers
AcX=Wire.read()<<8|Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L) 
AcY=Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
AcZ=Wire.read()<<8|Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
Tmp=Wire.read()<<8|Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
GyX=Wire.read()<<8|Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
GyY=Wire.read()<<8|Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
GyZ=Wire.read()<<8|Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

// Serial.print("Accelerometer: ");
// Serial.print("X = "); Serial.print(AcX);
// Serial.print(" | Y = "); Serial.print(AcY);
// Serial.print(" | Z = "); Serial.println(AcZ);
//equation for temperature in degrees C from datasheet
// Serial.print("Temperature: "); 
//Serial.println(GyZ);

// Serial.print("Gyroscope: ");

// Serial.print("X = ");

if (digitalRead(7)== LOW){
GyX=map(GyX,600,6000,0,10);
Serial.print("x");
Serial.print(GyX);
Serial.print(" ");
mySer.print(GyX);
mySer.print(" ");
// Serial.print(" | Y = ");
GyY=map(GyY,600,6000,2,10);
Serial.print("y"); 
Serial.print(GyY);
Serial.print(" ");
mySer.print(GyY);
mySer.print(" ");
// Serial.print(" | Z = "); 
GyZ=map(GyZ,-600,6000,-3,10);
Serial.print("z");
Serial.print(GyZ);
Serial.println("u");
mySer.print(GyZ);
mySer.println(" ");
// Serial.println(" ");
//Serial.print(Tmp/340.00+36.53); Serial.println(" C "); 
delay(50);
}else{
Serial.println(".");
mySer.println(".");
}

}