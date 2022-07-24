/*the lib can be found here:https://github.com/claws/BH1750
 the project can be found here: https://github.com/Tbthanh/ET2000_project_smartlight
 */

#include <Wire.h> // adds I2C library 
#include <BH1750.h> // adds BH1750 library file 
const int relayPin = 13;        // relay pin is pin 13 on Arduino
const int pirinPin = 3;       // PIR pin is 3 on Arduino
int lightState = LOW;     // start with light turn off
BH1750FVI LightSensor;



void setup() //code in here only run once.
{
  pinMode(relayPin, OUTPUT);
  pinMode(pirinPin, INPUT); //digital LOW-HIGH (0V-3.3V)
  Serial.begin(9600);
  LightSensor.begin();
  LightSensor.SetAddress(Device_Address_L); //Address 0x23 follow the datasheet of "BH1750FVI"
  /*
  Set the address for this sensor
  you can use 2 different address
  Device_Address_H "0x5C"
  Device_Address_L "0x23"
  you must connect Addr pin to A3 .
  */
  LightSensor.SetMode(Continuous_H_resolution_Mode);
  Serial.println("Running...");
}



void loop()
{
  int vala = digitalRead(pirinPin);    
  // read PIR get HIGH or LOW
  uint16_t valb = LightSensor.GetLightIntensity();
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
/*from:https://www.instructables.com/BH1750-Digital-Light-Sensor/
First Many thanks for Claws , He created a library for BH1750 , You can check it Out .

I prepared a library for it , Tried to solve some issue such like :

1) multi device connecting , You can connect 2 devices of BH1750 WIth different addresses , Depend on ADDR Pin status .

 If ADDR = LOW , The address will be 0x23

If ADDR = HIGH, The address will be 0x5C

*/
