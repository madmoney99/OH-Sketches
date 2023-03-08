
#define DCSBIOS_DEFAULT_SERIAL

#include <DcsBios.h>
//HID Panel for RHAUX PANEL
#include <Joystick.h>
#define NUMBUTTONS 1     // match to number of pins being used for HID
#define hookPin 8
// defining the total [#] of buttons and their pins
int SwitchOnPin[NUMBUTTONS] = {hookPin};    //add other pins here
//Store States
bool lastBtnState[NUMBUTTONS] = {0};      // match number of input pins, 3 would show as 0,0,0
bool btnState[NUMBUTTONS] = {0};      // same as above

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
  NUMBUTTONS, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

DcsBios::Switch2Pos hookLever("HOOK_LEVER", hookPin, true);

void setup() {
  DcsBios::setup();
  //Set Switch Pins to Inputs and Mag Pins to Outputs
    for (int i=0;i<NUMBUTTONS;i++){
      pinMode(SwitchOnPin[i], INPUT_PULLUP);
    }
  // Initialize Joystick Library
  Joystick.begin();
}

void loop() {
  DcsBios::loop();
  for (int i=0;i<NUMBUTTONS;i++)
  {
    int btnState = !digitalRead(SwitchOnPin[i]);
    if (btnState != lastBtnState[i])
    {
      Joystick.setButton(i, btnState);
      lastBtnState[i] = btnState;
    }
  }
   delay(50);
}
