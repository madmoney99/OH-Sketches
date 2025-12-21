#include <Wire.h>
#include "TCA9534.h"
#include <Joystick.h>

// Define the TCA9534 objects for each row
TCA9534 ddiButtons[4] = {
  TCA9534(0x23), //Left Row
  TCA9534(0x20), //Top Row
  TCA9534(0x22), //Right Row
  TCA9534(0x21)  //Bottom Row
};

const int buttonCountPerRow = 5;
const int totalButtons = 4 * buttonCountPerRow;

// Create Joystick object
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_GAMEPAD,
                   totalButtons, 0, // Button Count, Hat Switch Count
                   false, false, false, // X, Y, Z
                   false, false, false, // Rx, Ry, Rz
                   false, false,       // Rudder, Throttle
                   false, false, false); // Accelerator, Brake, Steering

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(6, OUTPUT);

  // Initialize each TCA9534 and set pins as inputs
  for (int i = 0; i < 4; i++) {
    if (!ddiButtons[i].Begin()) {
      Serial.print("Failed to initialize TCA9534 at address 0x");
      //Serial.println(ddiButtons[i].getAddress(), HEX);
      while (1); // Halt if initialization fails
    }
    for (int j = 0; j < buttonCountPerRow; j++) {
      ddiButtons[i].PinMode(j, INPUT);
    }
  }

  // Initialize Joystick Library
  Joystick.begin();
}

void loop() {
  int buttonIndex = 0;

  // Read and send button states
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < buttonCountPerRow; j++) {
      int buttonState = ddiButtons[i].DigitalRead(j);
      bool pressed = (buttonState == LOW); // Assuming LOW means pressed
      Joystick.setButton(buttonIndex, pressed);
      buttonIndex++;
    }
  }

  delay(50); // Small delay to avoid flooding the USB communication
}