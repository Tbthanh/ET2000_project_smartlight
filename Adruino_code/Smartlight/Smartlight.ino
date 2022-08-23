/*the lib can be found here:https://github.com/claws/BH1750
 the project can be found here: https://github.com/Tbthanh/ET2000_project_smartlight
 */

#include <Wire.h> // adds I2C library 
#include <BH1750.h> // adds BH1750 library file 

const int relayPin = 10;        // relay pin is pin 13 on Arduino
const int pirinPin = 4;       // PIR pin is 3 on Arduino
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
  Serial.println(F("BH1750 Test"));
}

void loop()
{
  int vala = digitalRead(pirinPin);    
  // read PIR get HIGH or LOW
  uint16_t valb = lightMeter.readLightLevel();
  // Get Lux value in unasignint 2 bytes unsigned  0 to 65535
  //print the valb to serial monitor/ for debugging only
  Serial.print("Light: ");
  Serial.print(valb);
  Serial.println(" lux");
  Serial.print("|| motion:");
  Serial.println(vala);

  //
  if(lightState == LOW) //light is off
  {
    if(valb<=100)
    {
      if(vala==HIGH)
      {
        digitalWrite(relayPin, HIGH);
        lightState=HIGH; 
        Serial.println("Light on");
        //delay for the sensor sake. (I saw it in the guide hehe)
      }  
    }
  }
  else //Light is on
  {
    if(valb>700) //turn the light off when enviroment is bright enough
    {
        //delay(9700); // the delay is big enough for the sensor to not go heywild
        digitalWrite(relayPin, LOW);
        lightState=LOW;
        Serial.println("Light off");
    }
    else
    {
        if(vala==HIGH)
        {
          digitalWrite(relayPin, HIGH);
          lightState=HIGH;
          //delay for the sensor sake. (I saw it in the guide hehe)
        }  
        else
        {
          delay(1000);
           digitalWrite(relayPin, LOW);
          lightState=LOW;  
          Serial.println("Light off");
        }
    }  
  }
  delay(1000);
}
