int buzzer = 4;   //declares buzzer @pin 5
int FSRanalogpin = A0; //declares the FSR @analogpin A0
int FSRvalue ;  //saves the analog value as integer

void setup()
{
Serial.begin (9600);
pinMode(FSRanalogpin,INPUT); //sets the FSR as the input
pinMode(buzzer,OUTPUT);   //sets the buzzer as the output
}

void loop()
{
FSRvalue = analogRead(FSRanalogpin); //reads the FSR and store it in integer
int FSR1= FSRvalue;
Serial.println(FSRvalue);
      
if(FSRvalue <10)
  {
    digitalWrite(buzzer, HIGH);  
  }
  else
  {
    digitalWrite(buzzer, LOW);  
  }
  

          delay(500);
}
