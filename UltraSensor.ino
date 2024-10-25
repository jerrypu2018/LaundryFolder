#include <Servo.h>

// Define the pins for the HC-SR04 sensor
const int trigPin = 5;
const int echoPin = 6;

// Define variables for duration and distance
long duration;
int distance;

// Servo object
Servo myServo;

// Variables for tracking the trigger state and sequence execution
bool triggered = false;
bool firstRun = true;

void setup() {
  // Set the pin modes for the ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach the servo motor to pin 11 and set to initial position
  myServo.attach(11);
  myServo.write(0);  // Default position (0 degrees)

  delay(100);  // Small delay to stabilize at power-on
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

  // Ensure the sensor does not trigger the sequence on power-up
  if (firstRun) {
    if (distance >= 5) {  // Ignore anything greater than the detection threshold
      firstRun = false;
    }
  } else {
    // Only trigger the sequence if the object is detected within 5 cm and not already triggered
    if (distance < 5 && !triggered) {
      triggered = true;  // Set triggered to true to block further sequences

      // Wait for 3 seconds before starting the servo sequence
      delay(3000);

      // Move the servo to 180 degrees
      myServo.write(180);

      // Wait for 2 seconds
      delay(2000);

      // Move the servo back to 0 degrees
      myServo.write(0);

      // Wait 12 seconds before scanning again
      delay(12000);

      // Reset the triggered flag to allow new triggers after the delay
      triggered = false;
    }
  }

  // Small delay to allow loop timing
  delay(200);
}
