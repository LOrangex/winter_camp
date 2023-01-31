#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <Servo.h>
#include <DHT.h>

#define dhtPin 9
#define servo1Pin 10
#define servo2Pin 11
#define photoPin A0

Servo servo1; 
Servo servo2; 
DHT myDHT (dhtpin, DHT11); 

void setup() {
    pinMode(photoPin, INPUT); 
    servo1.attach(servo1Pin);
    servo2.attach(servo2Pin); 
    myDHT.begin();
}

void loop() {
    if(myDHT.readHumidity()>80 || analogRead(photoPin)>100){
       servo1.write(90);
       servo2.write(90); 
       delay(500);
    }
}

