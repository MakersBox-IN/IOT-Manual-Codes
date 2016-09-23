#include <SPI.h>
#include <Ethernet.h>
#include <dht.h>

dht DHT;
const int dhtPin = 2;

int chk;
float hum;
float temp;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress ip(000, 000, 000, 000); //your static ip

char thingSpeakAddress[] = "api.thingspeak.com";
String writeAPIKey = "thingspeak api key";
const int updateThingSpeakInterval = 10 * 1000;     


long lastConnectionTime = 0; 
boolean lastConnected = false;
int failedCounter = 0;

EthernetClient client;


void setup() {
  Serial.begin(9600);
   }

void loop() {
  chk = DHT.read11(dhtPin); //use DHT.read22 in case of DHT-22
  hum = DHT.humidity;
  temp= DHT.temperature;
    
  String field1 = String(temp);
  String field2 = String(hum);

  Serial.println("Temperature="+field1);
  Serial.println("Humidity="+field2);
  
  if (client.available())
  {
    char c = client.read();
    Serial.print("Byte Received=");
    Serial.println(c);
  }
  // Disconnect from ThingSpeak
  if (!client.connected() && lastConnected)
  {
    Serial.println("...disconnected");
    Serial.println();
    
    client.stop();
  }
  
     // Update ThingSpeak
  
  //if(client.connected() && (millis() - lastConnectionTime > updateThingSpeakInterval))
  //{
    updateThingSpeak("field1="+field1+"&field2="+field2);
    //}
   
   // Check if Arduino Ethernet needs to be restarted
  if (failedCounter > 3 ) {startEthernet();}
  
  lastConnected = client.connected();

  delay(10000);
}


void updateThingSpeak(String tsData)
{
  if (client.connect(thingSpeakAddress, 80))
  {         
    Serial.println("Connecting to Thingspeak");
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n");
    client.print(tsData);
    
    lastConnectionTime = millis();
    
    if (client.connected())
    {
      Serial.println("Connected to ThingSpeak...");
      Serial.println();
      
      failedCounter = 0;
    }
    else
    {
      failedCounter++;
  
      Serial.println("Connection to ThingSpeak failed ("+String(failedCounter, DEC)+")");   
      Serial.println();
    }
    
  }
  else
  {
    failedCounter++;
    
    Serial.println("Connection to ThingSpeak Failed ("+String(failedCounter, DEC)+")");   
    Serial.println();
    
    lastConnectionTime = millis(); 
  }
  
}

void startEthernet()
{
 if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
}
else
Serial.println("Connected to ethernet using DHCP");
}
