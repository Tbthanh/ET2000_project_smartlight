/*the lib can be found here:https://github.com/claws/BH1750
 the project can be found here: https://github.com/Tbthanh/ET2000_project_smartlight
 */

#include <Wire.h> // adds I2C library 
#include <BH1750.h> // adds BH1750 library file 
const int relayPin = 13;        // relay pin is pin 13 on Arduino
const int pirinPin = 3;       // PIR pin is 3 on Arduino
const int phoresPin = 0;      // BH1750 pin is A0 on Arduino
int lightState = LOW;     // start with light turn off
int vala = 0;
int valb = 0;
 
void setup()
{
  pinMode(relayPin, OUTPUT);
  pinMode(pirinPin, INPUT); //digital 0/1 (0V-3.3V)
  pinMode(phoresPin,INPUT); //analoge of phores :(
  Serial.begin(9600);
}
 
void loop()
{
  vala = digitalRead(pirinPin);    // read PIR
  valb = analogRead(phoresPin);   //read photoresistor value
  if(lightState == LOW)//light is off
  {
    if(valb<120)
    {
      if(vala==HIGH)
      {
        digitalWrite(relayPin, HIGH);
        lightState=HIGH; 
      }  
    }
  }
  else //Light is on
  {
    if(valb>700) //dont know the real num of valb when light is on
    {
        delay(10000);
        digitalWrite(relayPin, LOW);
        lightState=LOW;
    }
    else
    {
        if(vala==HIGH)
        {
          digitalWrite(relayPin, HIGH);
          lightState=HIGH; 
        }  
        else
        {
          delay(10000);
          digitalWrite(relayPin, LOW);
          lightState=LOW;  
        }
    }  
  }

  
}
