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
LiquidCrystal_I2C MyLCD(0x27,16,2); 

void setup() {
    pinMode(photoPin, INPUT); 
    servo1.attach(servo1Pin);
    servo2.attach(servo2Pin); 
    myDHT.begin();
    MyLCD.init();  
    MyLCD.backlight();

}

void loop() {
    if(myDHT.readHumidity()>80 || analogRead(photoPin)>100){
       servo1.write(90);
       servo2.write(90); 
       delay(500);
    }
    else{
        servo1.write(0);
        servo2.write(0); 
        delay(500);
    }
    MyLCD.clear();
    MyLCD.setCursor(0,0); 
    MyLCD.print(MyDHT.readTemperature()); 
    MyLCD.print("C");
    MyLCD.setCursor(0,1); 
    MyLCD.print(MyDHT.readHumidity());
    MyLCD.print("%");
    delay(500);
}

