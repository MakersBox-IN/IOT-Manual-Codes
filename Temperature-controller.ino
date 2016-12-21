#include <RCSwitch.h> //only used for remote control switches, not used if you have a relay

#define aref_voltage 3.3         // we tie 3.3V to ARef and measure it with a multimeter!

//TMP36 Pin Variables
int tempPin = 1;        
int tempReading; 

float desiredTempC = 28; // which temperature to maintain

RCSwitch mySwitch = RCSwitch();  

void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);   
  // If you want to set the aref to something other than 5v
  analogReference(EXTERNAL);
  //enable RC switch transmissions on pin 10. 
  mySwitch.enableTransmit(8);
}
 
 
void loop(void) {
 
  tempReading = analogRead(tempPin);  
 
  // converting that reading to voltage, which is based off the reference voltage
  float voltage = tempReading * aref_voltage;
  voltage /= 1024.0; 
 
  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;  
  Serial.print(temperatureC); Serial.println(" degrees C");
 
  /* now convert to Fahrenheight
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  Serial.print(temperatureF); Serial.println(" degrees F");
   */
   
  if(temperatureC < desiredTempC){
    mySwitch.switchOn(1,1);
    Serial.println("Heater ON");
  }
  else{
    Serial.println("Heater OFF");
    mySwitch.switchOff(1,1);
  }
    
   
  delay(1000);
}
