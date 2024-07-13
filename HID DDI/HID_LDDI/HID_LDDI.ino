#include <Wire.h>
//Setup the DDI Buttons - Use library from @Balse on Discord - https://github.com/balzreber/TCA9534
#include "TCA9534.h"


// Define the TCA9534 objects for each row
TCA9534 ddiButtons[4] = {
  TCA9534(0x23), //Left Row
  TCA9534(0x20), //Top Row
  TCA9534(0x22), //Right Row
  TCA9534(0x21)  //Bottom Row
};

const int buttonCountPerRow = 5;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(6, OUTPUT);
  
  // Initialize each TCA9534 and set pins as inputs
  for (int i = 0; i < 4; i++) {
    if (!ddiButtons[i].Begin()) {
      Serial.print("Failed to initialize TCA9534 at address 0x");
      //Serial.println(ddiButtons[i].GetAddress(), HEX);
      while (1); // Halt if initialization fails
    }
    for (int j = 0; j < buttonCountPerRow; j++) {
      ddiButtons[i].PinMode(j, INPUT);
    }
  }
}

void loop() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < buttonCountPerRow; j++) {
      int buttonState = ddiButtons[i].DigitalRead(j);
      Serial.print("Row ");
      Serial.print(i);
      Serial.print(", Button ");
      Serial.print(j);
      Serial.print(": ");
      Serial.println(buttonState == LOW ? "Pressed" : "Released");
    }
  }
  delay(500); // Small delay to avoid flooding the serial monitor
}