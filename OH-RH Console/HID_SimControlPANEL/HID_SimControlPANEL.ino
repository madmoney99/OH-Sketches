//HID Panel for SIM CONTROL

#include <Joystick.h>

Joystick_ Joystick;

void setup() {
  // Initialize Button Pins
  // for digitalRead pins A0-A5 = 18-23
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);

  pinMode(10, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);

  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.begin();
}

// defining the total [#] of buttons and their pins
const int ButtonToPinMap[15] = {2,3,4,6,7,8,9,10,14,15,16,18,19,20,21};

int lastButtonState[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void loop() {

  for (int index = 0; index < 15; index++)
  {
    int currentButtonState = !digitalRead(ButtonToPinMap[index]);
    if (currentButtonState != lastButtonState[index])
    {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }

  delay(50);
}