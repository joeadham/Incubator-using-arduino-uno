#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <dht.h>
dht DHT;
#define dht_apin A1
LiquidCrystal_I2C lcd (0x27, 16,2);
const int BUTTON = 12;
const int LED1 = 8;
const int LED2 = 9;
const int LED3 = 10;
const int LED4 = 11;
int BUTTONstate = 0; 
bool buttonState = false;
//Relay

//THERMISTOR
int ThermistorPin = 0;
int Vo;
float R1 = 100000;
float logR2, R2, T, Tc;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void closeLeds(){
      digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
}

void openLeds(){
      digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
  }

void setup() 
{
 Serial.begin(9600);
 pinMode(3,OUTPUT);
 pinMode(4,OUTPUT);
 lcd.init();
 lcd.backlight();
 pinMode(BUTTON, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() {
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;

  lcd.print("Temp:"); 
  lcd.print(Tc);
  lcd.println("C");   

  delay(1000);
  lcd.clear();

//HUMIDITY SENSOR
 DHT.read11(dht_apin);
    Serial.print(DHT.temperature);
    lcd.print("humidity = ");
    lcd.print(DHT.humidity);
    lcd.print("%");
    delay(1000);
      lcd.clear();
//    lcd.print("dht_temp=");
//    lcd.print(DHT.temperature); 
// 
  delay(3000);//Wait 5 seconds before accessing sensor again.
  lcd.clear();
if(Tc > 30){
digitalWrite(3,HIGH);
digitalWrite(4,HIGH);
}
else{
digitalWrite(3,LOW);
digitalWrite(4,LOW);
}
 
  //Fastest should be once every two seconds.
  delay(60);  
  BUTTONstate = digitalRead(BUTTON);
  if (BUTTONstate == HIGH)
  {
    buttonState = !buttonState;
    if(buttonState){
      openLeds();
      }else{
        closeLeds();
      }
  }  
}
