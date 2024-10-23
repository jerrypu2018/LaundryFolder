#include <Servo.h>

// Define servo motor object
Servo servo1;

// Pin for the button
const int buttonPin = 2;

// Variables for button states
int prevButtonState = LOW;
int buttonState = LOW;

// Variable to track whether the sequence has been executed
bool sequenceExecuted = false;

// Flag to track servo attachment state
bool servoAttached = false;

void setup() {
  // Initialize button pin as input
  pinMode(buttonPin, INPUT_PULLUP);  // Enable internal pull-up resistor

  // Do not attach the servo yet, to avoid any unintended movement
  // servo1.detach(); is not needed yet since it hasn't been attached
}

void loop() {
  // Read the button state
  buttonState = digitalRead(buttonPin);

  // Debounce delay (optional)
  delay(20);  

  // Check for button press to attach the servo for the first time
  if (!servoAttached && buttonState == HIGH) {
    // Attach the servo only after the button is pressed for the first time
    servo1.attach(11);  // Attach the servo
    servo1.write(0);    // Set servo to initial position (0 degrees)
    delay(100);         // Small delay to allow servo to reach position
    servoAttached = true;  // Mark the servo as attached
  }

  // Once the servo is attached, allow it to respond to button presses
  if (servoAttached) {
    // Check for button press and release
    if (buttonState == HIGH && prevButtonState == LOW && !sequenceExecuted) {
      // Button pressed and sequence not executed yet
      executeServoSequence();
      sequenceExecuted = true;  // Mark sequence as executed
    } else if (buttonState == LOW && prevButtonState == HIGH) {
      // Button released
      sequenceExecuted = false;  // Reset sequence executed flag
    }
  }

  // Update previous button state
  prevButtonState = buttonState;
}

void executeServoSequence() {
  // Move the servo
  servo1.write(180);
  delay(1000);
  servo1.write(0);
  delay(1000);
}
