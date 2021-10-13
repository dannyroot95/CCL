#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "puertaelectrica-bf3d5-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "zYF4FBQeIUxx4XHMR1vpDAHbrdQvUTwIOR6fc3ui"
#define WIFI_SSID "WRZ"
#define WIFI_PASSWORD "Materdei20*"
#define RELAY 4

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(RELAY, OUTPUT);

  
}

void loop() {
   // get value 
   
  digitalWrite(RELAY, HIGH);
  
  if(Firebase.getString("status") == "open")
  {
    digitalWrite(RELAY, LOW);
    delay(1000);
  Firebase.setString("status", "closed");
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
     }
  }
}
