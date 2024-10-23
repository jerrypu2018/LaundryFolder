#include <Servo.h>

//Servo1 = Left/Right Panels
//Servo2 = Top Panel
//Servo3 = Trapdoor

// Define servo motor objects
Servo servo1;
Servo servo2;
Servo servo3;

// Pin for the button
const int buttonPin = 2;
// Button States
int prevButtonState = LOW;
int buttonState = LOW;

// Variable to track whether the sequence has been executed
bool sequenceExecuted = false;
// Variable to track if it's the first run
bool firstRun = true;

void setup() {
  // Initialize button pin as input
  pinMode(buttonPin, INPUT_PULLUP);

  // Attach the servo without moving it
  servo1.attach(9);
  servo1.write(90);

  servo2.attach(10);
  servo2.write(0);

  servo3.attach(11);
  servo3.write(180);

  delay(100);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (firstRun) {
    if (buttonState == HIGH) {
      firstRun = false;
    }
  } else {
    if (buttonState == HIGH && prevButtonState == LOW && !sequenceExecuted) {
      executeServoSequence();
      sequenceExecuted = true;
    } else if (buttonState == LOW && prevButtonState == HIGH) {
      // Button release and reset
      sequenceExecuted = false;
    }
  }

  prevButtonState = buttonState;
}


void executeServoSequence() {
  // Servo1
  servo1.write(180);
  delay(1500);
  servo1.write(90);
  delay(100);
  servo1.write(0);
  delay(2400);
  servo1.write(90);
  delay(1000);
 
  // Servo2
  servo2.write(155);
  delay(500);
  delay(1000);
  servo2.write(0);
  delay(500);
  delay(1000);
 
  // Servo3
  servo3.write(0);
  delay(700);
  delay(500);
  servo3.write(180);
  delay(700);
}
