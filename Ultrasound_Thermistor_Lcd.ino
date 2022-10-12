#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd (0x27, 16,2);
//ULTRASONIC SENSOR & BUZZER
int const trigPin = 8;
 int const echoPin = 7;
 int const buzzPin = 6;
 

//THERMISTOR
int ThermistorPin = 0;
int Vo; 
float R1 = 10000; 
float logR2, R2, T, Tc; 
//float Tf;
float c1 = 1.009249522e-03,
 c2 = 2.378405444e-04,
 c3 = 2.019202697e-07;



void setup() {
 Serial.begin(9600);
 lcd.init();
 lcd.backlight();
//ULTRASONIC & BUZZER 
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT);
pinMode(buzzPin, OUTPUT); 

}
void loop() {

//THERMISTOR
 Vo = analogRead(ThermistorPin);
 R2 = R1 * (1023.0 / (float)Vo - 1.0); 
logR2 = log(R2);
 T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); 
Tc = T - 273.15; 
//Tf = (Tc * 9.0)/ 5.0 + 32.0; Serial.print("Temperature: "); 
//Serial.print(Tf); 
//Serial.print(" F; "); 
Serial.print(Tc);
 Serial.println(" C"); 
delay(500); 


//ULTRASONIC & BUZZER 

int duration, distance;   
digitalWrite(trigPin, HIGH); 
delay(1); 
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
// Distance is half the duration devided by 29.1 (from datasheet) 
distance = (duration/2) / 29.1;
if (distance >= 50 ) {
 digitalWrite(buzzPin, HIGH);
 Serial.println(distance);
 lcd.setCursor(0,0);
lcd.print(distance);
 } 
else { 
digitalWrite(buzzPin, LOW); 
Serial.println(distance);
lcd.setCursor(0,0);
lcd.print("Distance: ");

lcd.print(distance);
} 
delay(60);
}
