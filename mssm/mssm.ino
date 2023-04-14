
#define BLYNK_TEMPLATE_ID "TMPLDLdCZ8YD"
#define BLYNK_TEMPLATE_NAME "Service Station monitoring"
#define BLYNK_AUTH_TOKEN "21O1_497BzkO4QxzVetIjnVCHq5750DU"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

const char auth[] = "21O1_497BzkO4QxzVetIjnVCHq5750DU";
const char* ssid = "shin";
const char* pass = "@22552255Vic";  


const int numBatteries = 3;
const int batteryPins[numBatteries] = { 34, 35, 36 };
const float voltageDividerRatio = 0.5;
const int numTanks = 3;
const int trigPins[numTanks] = { 19, 21, 23 };
const int echoPins[numTanks] = { 18, 22, 26 };
const float tankHeight = 10.0; // in centimeters

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // Measure battery voltages
  float voltages[numBatteries];
  for (int i = 0; i < numBatteries; i++) {
    voltages[i] = analogRead(batteryPins[i]) * 3.3 / 4095 * voltageDividerRatio + 2.34;
    float batteryPercentage = voltages[i];
    Serial.print("Battery ");
    Serial.print(i);
    Serial.print(" voltage: ");
    Serial.print(voltages[i], 2);
    Serial.print("V (");
    Serial.print(batteryPercentage);
    Serial.println("%)");
    //Blynk.virtualWrite(i, batteryPercentage);
  }
float b1 = map(voltages[0],66.905,88.531,0,100);
float b2 = map(voltages[1],66.905,88.531,0,100);
float b3 = map(voltages[2],66.905,88.531,0,100);
Blynk.virtualWrite(V1, b1);
Blynk.virtualWrite(V2, b2);
Blynk.virtualWrite(V3, b3);
  // Measure liquid levels
  float distances[numTanks];
  for (int i = 0; i < numTanks; i++) {
    digitalWrite(trigPins[i], LOW);
    delayMicroseconds(2);
    digitalWrite(trigPins[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPins[i], LOW);
    float duration = pulseIn(echoPins[i], HIGH);
    distances[i] = duration / 2.0 * 0.0343;
    float tankPercentage = map(distances[i], 0, tankHeight, 0, 100);
    Serial.print("Tank ");
    Serial.print(i);
    Serial.print(" level: ");
    Serial.print(distances[i], 2);
    Serial.print("cm (");
    Serial.print(tankPercentage);
    Serial.println("%)");
    //Blynk.virtualWrite(i + numBatteries, tankPercentage);
  }
Blynk.virtualWrite(V4, distances[0]);
Blynk.virtualWrite(V5,distances[1]);
Blynk.virtualWrite(V6,distances[2]);
  delay(1000);
  Blynk.run();
}