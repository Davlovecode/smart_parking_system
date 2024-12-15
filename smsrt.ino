#include <Servo.h>

Servo gateServo; // Servo object
const int irSensor = 9;     // IR sensor pin (digital pin 9)
const int servoPin = A1;    // Servo motor pin (analog pin A1)
const int gatePosOpen = 90; // Servo position when gate is open
const int gatePosClose = 0; // Servo position when gate is closed

void setup() {
  pinMode(irSensor, INPUT);  // Set IR sensor pin as input
  gateServo.attach(servoPin); // Attach servo to analog pin A0
  gateServo.write(gatePosClose); // Initialize gate to closed position
  Serial.begin(9600); // Start serial monitor for debugging
}

void loop() {
  int irValue = digitalRead(irSensor); // Read IR sensor value

  if (irValue == LOW) { // Object detected (IR sensor gives LOW signal)
    Serial.println("Object Detected: Opening Gate...");
    gateServo.write(gatePosOpen); // Move servo to open position
    delay(2000); // Wait 2 seconds (keep gate open)
    gateServo.write(gatePosClose); // Move servo back to closed position
    Serial.println("Gate Closed");
  } else {
    Serial.println("No Object Detected");
  }

  delay(100); // Small delay for stability
}
