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


/*** @file HID_MASTER_PANEL.ino>
/** @author <Tony Goodale>
 * @date <Dec 11-22>
 * @brief <MASTER_PANEL DCS BIOS>
 *
 *
 * 
 */

#define DCSBIOS_DEFAULT_SERIAL

#include <DcsBios.h>
#include <Joystick.h>
//HID Panel for MASTER ARM PANEL
#define NUMBUTTONS 6
//Declare Pins
#define canopy1 10
#define canopy2 16
#define pin1 14
#define pin2 15
#define pin3 A0
#define pin4 A1

int SwitchOnPin[NUMBUTTONS] = {pin1,pin2,pin3,pin4,canopy1,canopy2};
//Store States
bool lastBtnState[NUMBUTTONS] = {0,0,0,0,0,0};
bool btnState[NUMBUTTONS] = {0,0,0,0,0,0};

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
  NUMBUTTONS, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering


void setup() {
  //Set Switch Pins to Inputs
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