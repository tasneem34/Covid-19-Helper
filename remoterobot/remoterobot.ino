#include <DHT.h>
#include <LiquidCrystal.h>
#include <IRremote.h>
#define RM1 7 // right motor forward  IN1a 
#define RM2 A1 // right motor backward IN2a 
#define speedRM 6 // Speed -ENA- of right motor PWM pin 
#define LM1 A2 // left motor backward IN3b 
#define LM2   A4 // left motor forward   IN4b 
#define speedLM 5 // Speed -ENA- of left motor PWM pin 
#define myDHTPIN A0
#define myDHTTYPE DHT11
#define puzzer A5 // puzeer pin 
#define RECV_PIN  A3
IRrecv irrecv(RECV_PIN);
decode_results results;
//LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
DHT myDHT(myDHTPIN, myDHTTYPE);

void setup()
{
pinMode(LM1, OUTPUT);
pinMode(LM2, OUTPUT);
pinMode(RM1, OUTPUT);
pinMode(RM2, OUTPUT);
pinMode(RM2, OUTPUT);
pinMode(puzzer, OUTPUT);
lcd.begin(16, 2);
myDHT.begin();
irrecv.enableIRIn();
}


void loop()
{
  delay(500);
  lcd.clear();
  DHTsenseor();
  
 if (irrecv.decode(&results)){
        // To print the value of the pressed button
        Serial.println(results.value, HEX);
switch(results.value)
  {
    case 0xFF906F   : // " + " switch to make the robote walk Forward
          Forward ();
        break;
    
    case 0xFFA857   : // " - " switch to make the robote walk Backward
           Backward ();
        break;
    
    case 0xFF02FD    : // " << "  switch to make the robote Turn Left 
             TurnLeft ();
        break;
    
    case 0xFFC23D    : // " >> "  switch to make the robote Turn Right
            TurnRight ();
        break;
        
    case 0xFFA25D   : // " OFF/ON "  switch to make the robote Stop 
                Stop ();
        break; 
    
  }
  irrecv.resume();
 }
 


 
}

void Forward ()
{
digitalWrite(LM1, LOW );
digitalWrite(LM2, HIGH);
digitalWrite(RM1, HIGH);
digitalWrite(RM2, LOW);
analogWrite (speedRM,70);
analogWrite (speedLM,70);
}

void Stop ()
{
digitalWrite(LM1, LOW);
digitalWrite(LM2, LOW);
digitalWrite(RM1, LOW);
digitalWrite(RM2, LOW);
analogWrite (speedRM,0);
analogWrite (speedLM,0);
}

void TurnRight ()
{
digitalWrite(LM1, LOW);
digitalWrite(LM2, HIGH);
digitalWrite(RM1, LOW);
digitalWrite(RM2, LOW);
analogWrite (speedRM,0);
analogWrite (speedLM,70);
}

void TurnLeft ()
{
digitalWrite(LM1, LOW);
digitalWrite(LM2, LOW);
digitalWrite(RM1, HIGH);
digitalWrite(RM2, LOW);
analogWrite (speedRM,70);
analogWrite (speedLM,0);
}
void Backward ()
{
digitalWrite(LM1, HIGH );
digitalWrite(LM2, LOW);
digitalWrite(RM1, LOW);
digitalWrite(RM2, HIGH);
analogWrite (speedRM,70);
analogWrite (speedLM,70);
}
void DHTsenseor()
{
 float h = myDHT.readHumidity();
 float t = myDHT.readTemperature();
        
           lcd.setCursor(0,0);
           lcd.print("Humidty= ");
           lcd.print(h);
           lcd.print(" %");
          
           lcd.setCursor(0, 1);
           lcd.print("Temp = ");
           lcd.print(t);
           lcd.print(" C");
 if (h<40||t<25)
  {
    myTone(puzzer,899,1000);
    delay(1000);
    
    
  }
 
  
}
 void myTone(byte pin, uint16_t frequency, uint16_t duration)
{ // input parameters: Arduino pin number, frequency in Hz, duration in milliseconds
  unsigned long startTime=millis();
  unsigned long halfPeriod= 1000000L/frequency/2;
  pinMode(pin,OUTPUT);
  while (millis()-startTime< duration)
  {
    digitalWrite(pin,HIGH);
    delayMicroseconds(halfPeriod);
    digitalWrite(pin,LOW);
    delayMicroseconds(halfPeriod);
  }
  pinMode(pin,INPUT);
}
