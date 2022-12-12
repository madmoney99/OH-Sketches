/**************************************************************************************
 *        ____                   _    _                       _
 *       / __ \                 | |  | |                     | |
 *      | |  | |_ __   ___ _ __ | |__| | ___  _ __ _ __   ___| |_
 *      | |  | | '_ \ / _ \ '_ \|  __  |/ _ \| '__| '_ \ / _ \ __|
 *      | |__| | |_) |  __/ | | | |  | | (_) | |  | | | |  __/ |_
 *       \____/| .__/ \___|_| |_|_|  |_|\___/|_|  |_| |_|\___|\__|
 *             | |
 *             |_|
 *
 *
 *   Project OpenHornet
 *
 *   This Project is released under the Creative Commons 
 *   Atribution - Non Comercal - Share Alike License.
 *   
 *   CC BY-NC-SA 3.0
 *   
 *   You are free to:
 *   - Share — copy and redistribute the material in any medium or format
 *   - Adapt — remix, transform, and build upon the material
 *   The licensor cannot revoke these freedoms as long as you follow the license terms.
 *   
 *   Under the following terms:
 *   - Attribution — You must give appropriate credit, provide a link to the license, 
 *     and indicate if changes were made. You may do so in any reasonable manner, 
 *     but not in any way that suggests the licensor endorses you or your use.
 *   - NonCommercial — You may not use the material for commercial purposes.
 *   - ShareAlike — If you remix, transform, or build upon the material, 
 *     you must distribute your contributions under the same license as the original.
 *     
 *   No additional restrictions — You may not apply legal terms or technological 
 *   measures that legally restrict others from doing anything the license permits.
 *   
 *   More Information about the license can be found under:
 *   https://creativecommons.org/licenses/by-nc-sa/3.0/
 *   
 *   
 *   This Project uses Doxygen as a documentation generator.
 *   Please use Doxigen capable comments.
 *   
 **************************************************************************************/


/*** @file SIM_PANEL.ino>
/** @author <Tony Goodale>
 * @date <Dec 9-22>
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

#define DCSBIOS_DEFAULT_SERIAL
#include "DcsBios.h"
#include "Joystick.h"

//Declare Pins
int SwitchOnPin[4] = {2,3,4,5};
int MagPin[4] = {18,19,20,21};
int holdCount[8] = {0,0,0,0,0,0,0,0};
int t = 0;

//Store States
bool lastBtnState[4] = {0,0,0,0};
bool btnState[4] = {0,0,0,0};

//Define Joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  8, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

//How long to hold the button in game (in milliseconds)
int hold = 100;

//DCSBIOS Stuff
void onApuControlSwChange(unsigned int newValue)  {digitalWrite(MagPin[0],!newValue);}
void onLtdRSwChange(unsigned int newValue)        {digitalWrite(MagPin[1],!newValue);}
void onFuelDumpSwChange(unsigned int newValue)    {digitalWrite(MagPin[2],!newValue);}
void onLaunchBarSwChange(unsigned int newValue)   {digitalWrite(MagPin[3],!newValue);}

DcsBios::IntegerBuffer apuControlSwBuffer(0x74c2, 0x0100, 8, onApuControlSwChange);
DcsBios::IntegerBuffer ltdRSwBuffer(0x74c8, 0x4000, 14, onLtdRSwChange);
DcsBios::IntegerBuffer fuelDumpSwBuffer(0x74b4, 0x0100, 8, onFuelDumpSwChange);
DcsBios::IntegerBuffer launchBarSwBuffer(0x7480, 0x2000, 13, onLaunchBarSwChange);

void setup() {
  DcsBios::setup();
  //Set Switch Pins to Inputs and Mag Pins to Outputs
    for (int i=0;i<4;i++){
      pinMode(SwitchOnPin[i], INPUT_PULLUP);
      pinMode(MagPin[i], OUTPUT);
      digitalWrite(MagPin[i],1);
    }
  Joystick.begin();
}

void loop(){
  DcsBios::loop();
  delay(10); //Delay required for DCSBios to complete communications 
  t = millis();
  for (int i=0;i<4;i++){
    btnState[i] = digitalRead(SwitchOnPin[i]);
    if (btnState[i] != lastBtnState[i]){
      lastBtnState[i] = btnState[i];
      if (btnState[i] == false){
        Joystick.pressButton(i*2);
        holdCount[i*2] = t;
      }
      if(btnState[i] == true) {
        Joystick.pressButton(i*2+1);
        holdCount[i*2+1] = t;
      }
    }
  }
  for (int b=0;b<8;b++){
    if(t > holdCount[b] + hold) {
      Joystick.releaseButton(b);
    }
  }
}