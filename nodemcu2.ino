#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <Wire.h>
#define BLYNK_TEMPLATE_ID "TMPL3-d_7rFoR"
#define BLYNK_TEMPLATE_NAME "carparking"

#include <BlynkSimpleEsp8266.h>

// Pin Definitions for IR Sensors
#define IR_SENSOR_1_PIN 5  // IR sensor 1 connected to D1 pin
#define IR_SENSOR_2_PIN 4  // IR sensor 2 connected to D2 pin

// Blynk Auth Token (replace with your Blynk Auth Token)
char auth[] = "ol7iAM8MDfCnSGOQo4-_ptr7g4iw-Y0I" ; // Replace with your actual Auth Token

// Wi-Fi credentials
char ssid[] = "Devs";
char pass[] = "devanshu123";

// Parking status variables
bool isCarInSpot1 = false;
bool isCarInSpot2 = false;

void setup() {
  Serial.begin(9600);  // Start serial communication for debugging

  // Set up IR sensor pins as input
  pinMode(IR_SENSOR_1_PIN, INPUT);
  pinMode(IR_SENSOR_2_PIN, INPUT);

  // Connect to Wi-Fi
  Blynk.begin(auth, ssid, pass);

  // Debugging Wi-Fi connection
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
    delay(1000);
  }
  Serial.println("Connected to Wi-Fi");

  // Initialize parking spots status (No car)
  Blynk.virtualWrite(V0, "Empty");  // Parking Spot 1
  Blynk.virtualWrite(V1, "Empty");  // Parking Spot 2
}

void loop() {
  Blynk.run();  // Blynk.run() is essential for maintaining the connection to Blynk app

  // Debugging sensor states
  Serial.println("Sensor 1: " + String(digitalRead(IR_SENSOR_1_PIN)));
  Serial.println("Sensor 2: " + String(digitalRead(IR_SENSOR_2_PIN)));

  // Check if a car is detected in Parking Spot 1
  isCarInSpot1 = digitalRead(IR_SENSOR_1_PIN) == LOW;  // Active-low sensor (car detected when LOW)
  if (isCarInSpot1) {
    Blynk.virtualWrite(V0, "Occupied");  // Update status on Blynk app for Spot 1
  } else {
    Blynk.virtualWrite(V0, "Empty");  // Update status on Blynk app for Spot 1
  }

  // Check if a car is detected in Parking Spot 2
  isCarInSpot2 = digitalRead(IR_SENSOR_2_PIN) == LOW;  // Active-low sensor (car detected when LOW)
  if (isCarInSpot2) {
    Blynk.virtualWrite(V1, "Occupied");  // Update status on Blynk app for Spot 2
  } else {
    Blynk.virtualWrite(V1, "Empty");  // Update status on Blynk app for Spot 2
  }

  delay(1000);  // Delay to prevent constant polling (1 second)
}
