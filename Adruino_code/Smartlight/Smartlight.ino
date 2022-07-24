/*the lib can be found here:https://github.com/claws/BH1750
 the project can be found here: https://github.com/Tbthanh/ET2000_project_smartlight
 */

#include <Wire.h> // adds I2C library 
#include <BH1750.h> // adds BH1750 library file 


const int relayPin = 13;        // relay pin is pin 13 on Arduino
const int pirinPin = 3;       // PIR pin is 3 on Arduino
int lightState = LOW;     // start with light turn off
BH1750 lightMeter;


void setup() //code in here only run once.
{
  pinMode(relayPin, OUTPUT);
  pinMode(pirinPin, INPUT); //digital LOW-HIGH (0V-3.3V)
  Serial.begin(9600);
  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  // On esp8266 devices you can select SCL and SDA pins using Wire.begin(D4, D3);
  Wire.begin();
  lightMeter.begin();
  Serial.println(F("Running..."));
}


void loop()
{
  int vala = digitalRead(pirinPin);    
  // read PIR get HIGH or LOW
  uint16_t valb = lightMeter.readLightLevel();
  // Get Lux value in unasignint 2 bytes unsigned  0 to 65535
  
  //these serial.comand just for the sake of debugging :))
  Serial.print("Light: ");
  Serial.print(valb);
  Serial.println(" lux");
  if(lightState == LOW) //light is off
  {
    if(valb<=120)
    {
      if(vala==HIGH)
      {
        digitalWrite(relayPin, HIGH);
        lightState=HIGH; 
        Serial.print("Light on");
        delay(1000); 
        //delay for the sensor sake. (I saw it in the guide hehe)
      }  
    }
  }
  else //Light is on
  {
    if(valb>270) //turn the light off when enviroment is bright enough
    {
        delay(10000); // the delay is big enough for the sensor to not go heywild
        digitalWrite(relayPin, LOW);
        lightState=LOW;
    }
    else
    {
        if(vala==HIGH)
        {
          digitalWrite(relayPin, HIGH);
          lightState=HIGH;
          delay(1000); 
          //delay for the sensor sake. (I saw it in the guide hehe)
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
