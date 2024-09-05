#include <SoftwareSerial.h>   
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define trigger D4
#define echo D3     
float times=0;
int distance=0;
// Replace with your network credentials
const char* ssid     = "DESKTOP-FQOGVSC";
const char* password = "Ashik0050";


void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}



void loop() {

  digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 digitalWrite(trigger,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 times=pulseIn(echo,HIGH);
 int distance=times*340/20000;

 //Serial.println("Distance:");
 Serial.println(distance);
 //Serial.println(" cm");
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
    WiFiClient client; // Create a WiFiClient object
    http.begin(client, "http://192.168.43.204/ultrasonic/data.php?cm=" + String(distance));   //Specify request destination
    
    int httpCode = http.GET();                                  //Send the request
  
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);             //Print the response payload
 
    }
 
    http.end();   //Close connection
 
  }
 
  delay(1000);    //Send a request every 30 seconds
}
