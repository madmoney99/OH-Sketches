
/*** @file SIM_PANEL.ino>
/** @author <Tony Goodale>
 * @date <Mar20 23>
 * @brief <SIM PANEL DCS BIOS>
 *
 *Ideas
Toggles
- Rearm menu

Rotary
- Cockpit
- LSO
- Bomb
- Missile
- F10 Map
 * 
 */

#include "Joystick.h"
#define NUMBUTTONS 15
#define hdtrk1 4 
#define hdtrk2 3
#define time 2 
#define toggle1 A0 
#define toggle2 A1
#define game1 A2
#define game2 A3
#define rot1 15
#define rot2 14
#define rot3 16
#define rot4 10
#define rot5 9
#define rot6 8
#define rot7 7 
#define rot8 6

// defining the total [#] of buttons and their pins
int SwitchOnPin[NUMBUTTONS] = {hdtrk1,hdtrk2,time,toggle1,toggle2,game1,game2,rot1,rot2,rot3,rot4,rot5,rot6,rot7,rot8};
//Store States
bool lastBtnState[NUMBUTTONS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool btnState[NUMBUTTONS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
  NUMBUTTONS, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

void setup() {
  //Set Switch Pins to Inputs and Mag Pins to Outputs
    for (int i=0;i<NUMBUTTONS;i++){
      pinMode(SwitchOnPin[i], INPUT_PULLUP);
    }
  // Initialize Joystick Library
  Joystick.begin();
}

void loop() {
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