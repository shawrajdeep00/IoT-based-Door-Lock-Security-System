#include <ThingSpeak.h>               // add library
#include <ESP8266WiFi.h>

WiFiClient  client;
unsigned long counterChannelNumber = 1310019;                // Channel ID
const char * myCounterReadAPIKey = "8U4AC74HDTI7AAFW";      // Read API Key
const char * myCounterWriteAPIKey = "SU1XT89C2EIMWR5L";     // Write API Key

const int digitalPin = D6;                                   // ESP8266 Analog Pin ADC0 = A0
int sensorNewValue = 0;                                     // value read from the pot
int sensorOldValue = 0;   

void setup()
{
  Serial.begin(115200);
  Serial.println();
  pinMode(digitalPin , INPUT);
  WiFi.begin("Rajdeep's Wifi", "a2b2c2d2");                 // write wifi name & password           

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
}

void loop() 
{
  sensorOldValue = sensorNewValue;
  sensorNewValue = digitalRead(digitalPin);          // read the analog in value
  if(sensorOldValue != sensorNewValue)
  {
    ThingSpeak.writeField(counterChannelNumber , 1 ,sensorNewValue  , myCounterWriteAPIKey);
    Serial.println(sensorNewValue);                
  }
  delay(50);
}
