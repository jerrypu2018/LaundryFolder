#include <Servo.h>

// Servo1 = Left/Right Panels
// Servo2 = Top Panel
// Servo3 = Trapdoor

// PIN 5 = trigPin
// PIN 6 = echoPin
// PIN 9 = Left/Right Panels
// PIN 10 = Top Panel
// PIN 11 = Trapdoor
// PIN 13 = Buzzer

// Define servo motor objects
Servo servo1;
Servo servo2;
Servo servo3;

// Define the pins for the HC-SR04 sensor
const int trigPin = 5;
const int echoPin = 6;
const int buzzerPin = 13;

// Define variables for duration and distance
long duration;
int distance;

// Variables for tracking the trigger state and sequence execution
bool triggered = false;
bool firstRun = true;

void setup() {
  // Set the pin modes for the ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  // Attach servos and set initial positions
  servo1.attach(9);
  servo1.write(90);

  servo2.attach(10);
  servo2.write(0);

  servo3.attach(11);
  servo3.write(180);

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
    // Trigger the sequence only if an object is within 5 cm and not already triggered
    if (distance < 5 && !triggered) {
      triggered = true;  // Block further sequences until reset

      // Wait for 2 seconds upon detection of shirt
      delay(2000);

      // Buzzer countdown of 3 seconds
      buzzerCountdown();

      delay(500);

      // Execute the servo sequence
      executeServoSequence();

      // Wait 1 second before scanning for the next trigger
      // MIGHT REMOVE LATER
      delay(1000);

      // Reset the triggered flag to allow new triggers
      triggered = false;
    }
  }

  // Small delay to allow loop timing
  delay(200);
}

void executeServoSequence() {
  // Servo1 sequence
  servo1.write(165);
  delay(1500);
  servo1.write(90);
  delay(100);
  servo1.write(15);
  delay(2400);
  servo1.write(90);
  delay(1000);

  // Servo2 sequence
  servo2.write(155);
  delay(500);
  delay(1000);
  servo2.write(0);
  delay(500);
  delay(1000);

  // Servo3 sequence
  servo3.write(0);
  delay(700);
  delay(500);
  servo3.write(180);
  delay(700);
}

// Function to countdown with the buzzer for 4 seconds
void buzzerCountdown() {
  for (int i = 0; i < 2; i++) {    // Play 600 Hz tone for the first two intervals
    tone(buzzerPin, 600);          // Play 600 Hz tone
    delay(500);                    // Wait for 500ms (tone on)
    noTone(buzzerPin);             // Stop tone
    delay(500);                    // Wait for 500ms (tone off)
  }

  // Play 1000 Hz tone for the third and final interval
  tone(buzzerPin, 800);           // Play 1000 Hz tone
  delay(500);                      // Wait for 500ms (tone on)
  noTone(buzzerPin);               // Stop tone
  delay(500);                      // Wait for 500ms (tone off)
}
