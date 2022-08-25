/*the lib can be found here:https://github.com/claws/BH1750
 the project can be found here: https://github.com/Tbthanh/ET2000_project_smartlight
 */

#include <Wire.h> // adds I2C library 
#include <BH1750.h> // adds BH1750 library file 

const int relayPina = 10;        // relay pin is pin 13 on Arduino
const int relayPinb = 9;
int lightState = LOW;     // start with light turn off
BH1750 lightMeter;

void setup() //code in here only run once.
{
  Serial.begin(9600);
  pinMode(relayPina, OUTPUT);
  pinMode(relayPinb, OUTPUT);
  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  // On esp8266 devices you can select SCL and SDA pins using Wire.begin(D4, D3);
  Wire.begin();
  lightMeter.begin();
  Serial.println(F("BH1750 Test"));
}

void loop()
{
  uint16_t valb = lightMeter.readLightLevel();
  // Get Lux value in unasignint 2 bytes unsigned  0 to 65535
  //print the valb to serial monitor/ for debugging only
  digitalWrite(relayPina, LOW);
  digitalWrite(relayPinb, HIGH);
  Serial.println(valb);
  delay(500);
}
