#define BLYNK_TEMPLATE_ID "TMPLMwNIfFv7"
#define BLYNK_TEMPLATE_NAME "FanProject"
#define BLYNK_AUTH_TOKEN "f7Bd9iotBZ40eEN0gquXt-dQQOgWoy30"
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiManager.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
WiFiManager wifiManager;

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";
int fanonline = false;

BLYNK_WRITE(V0) {
  int value = param.asInt();
  if ( value == 1 && fanonline == true ) {
    digitalWrite(D1, 0);
    digitalWrite(D2, 1);
    digitalWrite(D3, 1);
  } else if ( value == 2 && fanonline == true )  {
    digitalWrite(D1, 1);
    digitalWrite(D2, 0);
    digitalWrite(D3, 1);
  } else if ( value == 3 && fanonline == true ) {
    digitalWrite(D1, 1);
    digitalWrite(D2, 1);
    digitalWrite(D3, 0);
  } else {
    digitalWrite(D1, 1);
    digitalWrite(D2, 1);
    digitalWrite(D3, 1);
  }
}


BLYNK_WRITE(V1) {
  int value = param.asInt();
  digitalWrite(D0, value);
  if ( value == 0 ) {
    fanonline = true;
  } else if (  value ==  1 ) {
    fanonline = false;
  }
  Blynk.syncVirtual(V0);  // will cause BLYNK_WRITE(V0) to be executed
}

BLYNK_CONNECTED() {
  Serial.println("( BLYNK ) CONNECTED SYNC.");
  Blynk.syncVirtual(V0);  // will cause BLYNK_WRITE(V0) to be executed
  Blynk.syncVirtual(V1);  // will cause BLYNK_WRITE(V1) to be executed
}

void setup() {
  Serial.begin(115200);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  wifiManager.autoConnect("( FAN ) WIFi-Config.");
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  Blynk.run();
}

