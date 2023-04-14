#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

const char auth[] = "21O1_497BzkO4QxzVetIjnVCHq5750DU";
const char* ssid = "shin";
const char* pass = "@22552255Vic";  


// Ultrasonic sensor pins
const int triggerPin1 = 19;
const int echoPin1 = 18;
const int triggerPin2 = 21;
const int echoPin2 = 22;
const int triggerPin3 = 23;
const int echoPin3 = 26;

// Battery voltage pins
const int batteryPin1 = 33;
const int batteryPin2 = 34;
const int batteryPin3 = 35;

// Virtual pin numbers for Blynk app
const int tank1LevelVPin = V4;
const int tank2LevelVPin = V5;
const int tank3LevelVPin = V6;
const int battery1VoltageVPin = V1;
const int battery2VoltageVPin = V2;
const int battery3VoltageVPin = V3;
const float voltageDividerRatio = 0.45;
void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // measure the liquid level in Tank 1
  digitalWrite(triggerPin1, LOW); // make sure the trigger pin is low
  delayMicroseconds(2); // wait for 2 microseconds
  digitalWrite(triggerPin1, HIGH); // send a 10 microsecond pulse to the trigger pin
  delayMicroseconds(10);
  digitalWrite(triggerPin1, LOW); // turn off the trigger pin
  
  unsigned long duration1 = pulseIn(echoPin1, HIGH); // measure the duration of the echo pulse
  float distance1 = duration1 * 0.034 / 2; // calculate the distance in centimeters
  
  float tank1Level = map(distance1, 0, 200, 0, 100); // convert the distance to a liquid level percentage
  
  // measure the liquid level in Tank 2
  digitalWrite(triggerPin2, LOW); // make sure the trigger pin is low
  delayMicroseconds(2); // wait for 2 microseconds
  digitalWrite(triggerPin2, HIGH); // send a 10 microsecond pulse to the trigger pin
  delayMicroseconds(10);
  digitalWrite(triggerPin2, LOW); // turn off the trigger pin
  
  unsigned long duration2 = pulseIn(echoPin2, HIGH); // measure the duration of the echo pulse
  float distance2 = duration2 * 0.034 / 2; // calculate the distance in centimeters
  
  float tank2Level = map(distance2, 0, 200, 0, 100); // convert the distance to a liquid level percentage
  
  // measure the liquid level in Tank 3
  digitalWrite(triggerPin3, LOW); // make sure the trigger pin is low
  delayMicroseconds(2); // wait for 2 microseconds
  digitalWrite(triggerPin3, HIGH); // send a 10 microsecond pulse to the trigger pin
  delayMicroseconds(10);
  digitalWrite(triggerPin3, LOW); // turn off the trigger pin
  
  unsigned long duration3 = pulseIn(echoPin3, HIGH); // measure the duration ofthe echo pulse
float distance3 = duration3 * 0.034 / 2; // calculate the distance in centimeters

float tank3Level = map(distance3, 0, 200, 0, 100); // convert the distance to a liquid level percentage

// measure the voltage of Battery 1
float battery1Voltage = analogRead(batteryPin1) * voltageDividerRatio / 4096.0 * 3.3; // convert the analog reading to voltage

// measure the voltage of Battery 2
float battery2Voltage = analogRead(batteryPin2) * voltageDividerRatio / 4096.0 * 3.3; // convert the analog reading to voltage

// measure the voltage of Battery 3
float battery3Voltage = analogRead(batteryPin3) * voltageDividerRatio / 4096.0 * 3.3; // convert the analog reading to voltage

// send the data to the Blynk app
Blynk.virtualWrite(tank1LevelVPin, tank1Level);
Blynk.virtualWrite(tank2LevelVPin, tank2Level);
Blynk.virtualWrite(tank3LevelVPin, tank3Level);
Blynk.virtualWrite(battery1VoltageVPin, battery1Voltage);
Blynk.virtualWrite(battery2VoltageVPin, battery2Voltage);
Blynk.virtualWrite(battery3VoltageVPin, battery3Voltage);

// print the data to the serial monitor
Serial.print("Tank 1 Level: ");
Serial.print(tank1Level);
Serial.print("%\t Battery 1 Voltage: ");
Serial.print(battery1Voltage);
Serial.println(" V");

Serial.print("Tank 2 Level: ");
Serial.print(tank2Level);
Serial.print("%\t Battery 2 Voltage: ");
Serial.print(battery2Voltage);
Serial.println(" V");

Serial.print("Tank 3 Level: ");
Serial.print(tank3Level);
Serial.print("%\t Battery 3 Voltage: ");
Serial.print(battery3Voltage);
Serial.println(" V");

delay(3000); // wait for 5 seconds before taking the next reading
Blynk.run();
}
