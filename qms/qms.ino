#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#define BLYNK_TEMPLATE_ID "TMPLG0aZHDDJ"
#define BLYNK_TEMPLATE_NAME "QMS"
#define BLYNK_AUTH_TOKEN "SMpphNIQLewxN4hgYrXUfC45vSLUJWyi"

//SoftwareSerial mySerial(10, 11); // RX, TX for serial communication
int pir1Pin = 35; // Pin for PIR sensor 1
int pir2Pin = 27; // Pin for PIR sensor 2
int queueSize = 0; // Counter for queue size
#include <BlynkSimpleEsp32.h>
#include <ThingSpeak.h>


// Blynk auth token
char auth[] = "SMpphNIQLewxN4hgYrXUfC45vSLUJWyi";
const char* ssid = "shin";
const char* password = "@22552255Vic";

// ThingSpeak information
const char* writeAPIKey = "GSA2QQ8EYLXLUYXA";
const char* readAPIKey = "XC2FCWVMW6P0ZR78"; 
const long channelID = 2090043; 
WiFiClient client;


void setup() {
  Serial.begin(9600); // Set baud rate for serial communication
  Blynk.begin(auth, ssid, password);  
  pinMode(pir1Pin, INPUT);
  pinMode(pir2Pin, INPUT);
 
}

void loop() {
  if (digitalRead(pir1Pin) == HIGH) {
    queueSize++; // Increment queue size when PIR sensor 1 detects motion
   // Serial.write('1'); // Send queue status 1 to serial port
   Blynk.virtualWrite(V1,queueSize);
  
    delay(1000); // Wait for 1 second to prevent multiple detections
  }
  if (digitalRead(pir2Pin) == HIGH && queueSize > 0) {
    queueSize--; // Decrement queue size when PIR sensor 2 detects motion and the queue is not empty
   // Serial.write('0'); // Send queue status 0 to serial port
  Blynk.virtualWrite(V1,queueSize);
    delay(1000); // Wait for 1 second to prevent multiple detections
  }
  if (queueSize > 0 && queueSize < 10) {
    Blynk.virtualWrite(V2,"Kindly Join the Queue");
    Serial.print("There are ");
    Serial.print(queueSize);
    Serial.println(" people in the queue.");
  } else if( queueSize > 10) {
     Blynk.virtualWrite(V2,"Please Wait,Queue Outmaxed");
    Serial.println("The queue is empty.");
  }else if (queueSize == 10) {
  // Blynk.virtualWrite(V2,"The Queue is filled up. Please wait");
    Serial.print("The Queue is filled up. Please wait ");
  } else {
   Blynk.virtualWrite(V2,"Queue is Empty");
  }
  ThingSpeak.begin(client);
  ThingSpeak.setField(1, queueSize);
  int statusCode = ThingSpeak.writeFields(channelID, writeAPIKey);
  if (statusCode == 200) {
    Serial.println("Data sent to ThingSpeak successfully.");
  } else {
    Serial.println("Failed to send data to ThingSpeak.");
  }
  delay(500);
  Blynk.run();
}
