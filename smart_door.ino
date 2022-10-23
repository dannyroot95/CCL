#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"

#define FIREBASE_HOST "puertaelectrica-bf3d5-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "zYF4FBQeIUxx4XHMR1vpDAHbrdQvUTwIOR6fc3ui"
//#define WIFI_SSID "WRZ"
//#define WIFI_PASSWORD "Materdei20*"
#define WIFI_SSID "ALFREDO"
#define WIFI_PASSWORD "@alfredoh1969"
#define RELAY 16

FirebaseData firebaseData;

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(5000);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  pinMode(RELAY, OUTPUT);

  
}

void loop() {
   // get value 
   
  digitalWrite(RELAY, HIGH);

  Firebase.getString(firebaseData, "status");
  String valueData = firebaseData.stringData();
  
  if(valueData == "open")
  {
    digitalWrite(RELAY, LOW);
    delay(1000);
    Firebase.setString(firebaseData,"status","closed");
  }
}
