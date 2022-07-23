/**/
const int relayPin = 13;        // relay pin is pin 13 on Arduino
const int pirinPin = 3;       // PIR pin is 3 on Arduino
const int phoresPin = 0;      //photoresistor pin is A0 on Arduino
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
  if(lightState == LOW)
  {
    if(valb<1000)
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
    else
    {
      delay(10000);
      digitalWrite(relayPin, LOW);
      lightState=LOW;      
    }  
  }
  else
  {
    if(valb>1000) //dont know the real num of valb when light is on
    {
        
    }  
  }

  
}
