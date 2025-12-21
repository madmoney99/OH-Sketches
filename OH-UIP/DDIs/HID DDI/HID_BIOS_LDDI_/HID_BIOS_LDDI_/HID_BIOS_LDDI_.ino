// DCS Bios Configuration - No RS458 Communcation
#define DCSBIOS_DEFAULT_SERIAL

// DCS-BIOS Configuration for RS485
//define DCSBIOS_RS485_SLAVE 2 //Set Correct Slave Number based on your configuration
#define TXENABLE_PIN 3 

#include "DcsBios.h" 
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

bool lastBtnState[20];
bool buttonState[20];
uint8_t inputRegister[4];
unsigned long lastDebounceTime[20];
unsigned long debounceDelay = 10;    // the debounce time; increase if the output flickers

void onConsoleIntLtChange(unsigned int newValue) {
      analogWrite(9,  map(newValue, 0, 65535, 0, 255));
}

DcsBios::IntegerBuffer consoleIntLtBuffer(0x7558, 0xffff, 0, onConsoleIntLtChange);

DcsBios::RotaryEncoder leftDdiBrtCtl("LEFT_DDI_BRT_CTL", "-3200", "+3200", A6, 7);
DcsBios::RotaryEncoder leftDdiContCtl("LEFT_DDI_CONT_CTL", "-3200", "+3200", A8, A10);

const byte leftDdiBrtSelectPins[3] = {A2, A1, A0};
DcsBios::SwitchMultiPos leftDdiBrtSelect("LEFT_DDI_BRT_SELECT", leftDdiBrtSelectPins, 3);
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
  DcsBios::setup();
  pinMode(6, OUTPUT);

  for (int i = 0; i < sizeof(lastBtnState) / sizeof(lastBtnState[0]); i++) {
    lastBtnState[i] = 0;
  }
  for (int i = 0; i < sizeof(ddiButtons) / sizeof(ddiButtons[0]); i++) {
    ddiButtons[i].Begin();
    for (int j = 0; j < 5; j++) {
      ddiButtons[i].PinMode(j, INPUT);
    }
    /*
    for (int j = 5; j < 5; j++) {
      ddiButtons[i].PinMode(j, OUTPUT);
    }
    */
  }

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
  DcsBios::loop();

  for (int i = 0; i < sizeof(ddiButtons) / sizeof(ddiButtons[0]); i++) {
    inputRegister[i] = ddiButtons[i].ReadAll();
    // i == 0; Left
    // i == 1; Top - Reversed (DDI v2)
    // i == 2; Right - Reversed (DDI v2)
    // i == 3; Bottom

    for (int j = 0; j < 5; j++) {
      int index; 
      if(i== 1 || i == 2){
         index = ((4-j) + 5 * i);
      }else{
         index = (j + 5 * i);
      }
      

      bool btnState = (inputRegister[i] >> (4 - j)) & 1;

      if(btnState != lastBtnState[index]) {
        lastDebounceTime[index] = millis();
      }

      if ((millis() - lastDebounceTime[index]) > debounceDelay) {
        if (btnState != buttonState[index]) {
            buttonState[index] = btnState;
                  char btnName[14];
                  sprintf(btnName, "LEFT_DDI_PB_%02d", index + 1);
                  DcsBios::tryToSendDcsBiosMessage(btnName, btnState == 1 ? "0" : "1");
        }
      }
      lastBtnState[index] = btnState;
    }
    
    
  }
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