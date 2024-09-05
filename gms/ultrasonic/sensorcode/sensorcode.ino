#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const byte trigger = 13;
const byte echo = 15;
float times;
int distance;
const char* ssid = "Aradhana Broadband #3019";
const char* password = "Ashik0050";
const char* serverAddress = "http://192.168.43.204/gms/ultrasonic/data.php";

void setup() {
  Serial.begin(9600);
  Serial.println("Connecting to WiFi...");
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.println("IP address: " + WiFi.localIP().toString());
}

void loop() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  times = pulseIn(echo, HIGH);
  distance = times * 0.034 / 2; // Convert time to distance in centimeters

  Serial.print("Distance: ");
  Serial.println(distance);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;
//    Serial.println("Sending HTTP request to: " + url);
    http.begin(client,"http://192.168.18.36/gms/data.php?cm="+String(distance));    
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Server response: " + payload);
    } else {
      Serial.println("Error sending HTTP request");
    }
    
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }

  delay(1000);
}

