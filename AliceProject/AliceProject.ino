

#include "thingProperties.h"
#include "DHT.h"

#define DHTPIN 12 // temp-humid sensor
#define RELAYPIN 4

#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  pinMode(RELAYPIN, OUTPUT); // water sensor
  pinMode(A0, INPUT); // 
  
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  loadWaterLevel();
  loadHumidTemp();
  
  
  
}

void loadWaterLevel() {
  waterlevel = analogRead(A0);
}


void onRelayChange() {
  if (relay == 0){
    digitalWrite(RELAYPIN,LOW );
  }else{
    digitalWrite(RELAYPIN, HIGH);
  }
}

void loadHumidTemp(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  humidity = h;
  temperature = t;
}
