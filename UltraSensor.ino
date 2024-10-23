#include <Servo.h>

// Define the pins for the HC-SR04 sensor
const int trigPin = 9;
const int echoPin = 10;

// Define variables for duration and distance
long duration;
int distance;

// Create a Servo object
Servo myServo;

void setup() {
  // Set the pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach the servo motor to pin 11
  myServo.attach(11);

  // Move the servo to the default position (0 degrees)
  myServo.write(0);
}

void loop() {
  // Send a 10us pulse to the HC-SR04 to trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, which returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in centimeters (speed of sound is 343 m/s)
  distance = duration * 0.034 / 2;

  // If the distance is less than 5 cm, move the servo to 180 degrees
  if (distance < 5) {
    myServo.write(180);
  } else {
    // If no object is detected, return to 0 degrees
    myServo.write(0);
  }

  // Wait for a short time before the next loop iteration
  delay(200);
}
