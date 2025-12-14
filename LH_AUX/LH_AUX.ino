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


/*** @file HID_LH_AUX_PANEL.ino>
/** @author <Tony Goodale>
 * @date <Dec 30-22>
 * @brief <HID_APU LH_AUX_PANEL DCS BIOS sketch in line with the OpenHornet Interconnect dated 2022-08-05>
 *
 * 
 */

#define DCSBIOS_DEFAULT_SERIAL

#include <DcsBios.h>
//HID Panel for RHAUX PANEL
//#include <Joystick.h>
#define NUMBUTTONS 12

/*#define lgUpDownPIn 3
#define downlockPIn A2
#define silencePin A3 */

#define flapUpPin A3
#define flapDownPin A2
#define launchBarPin A1
#define hookBypassPin A0

#define jettPin 15
#define jettSafePin 16
#define jettRackPin 14
#define antiskidPin 10

#define jettLPin 8
#define jettRPin 7
#define jettStoresPin 6
#define taxiLightPin 9

//#define parkingBPullPin 2
//#define parkingRot1Pin 3
//#define parkingRot2Pin 4

/*defining the total [#] of buttons and their pins
int SwitchOnPin[NUMBUTTONS] = {launchBarPin,flapUpPin,flapDownPin,taxiLightPin,antiskidPin,hookBypassPin,jettPin,jettLPin,jettSafePin,jettRPin,jettRackPin,jettStoresPin,parkingBPullPin,parkingRot1Pin,parkingRot2Pin};
//Store States
bool lastBtnState[NUMBUTTONS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool btnState[NUMBUTTONS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
  NUMBUTTONS, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering
*/
/* paste code snippets from the reference documentation here */
/*DcsBios::Switch2Pos gearLever("GEAR_LEVER", lgUpDownPIn);
DcsBios::Switch2Pos gearDownlockOverrideBtn("GEAR_DOWNLOCK_OVERRIDE_BTN", downlockPIn);
 */

DcsBios::Switch2Pos launchBarSw("LAUNCH_BAR_SW", launchBarPin);
DcsBios::Switch3Pos flapSw("FLAP_SW", flapUpPin, flapDownPin);
DcsBios::Switch2Pos selJettBtn("SEL_JETT_BTN", jettPin);
const byte selJettKnobPins[5] = {jettLPin, jettSafePin, jettRPin, jettRackPin, jettStoresPin};
DcsBios::SwitchMultiPos selJettKnob("SEL_JETT_KNOB", selJettKnobPins, 5);
DcsBios::Switch2Pos ldgTaxiSw("LDG_TAXI_SW", taxiLightPin);
DcsBios::Switch2Pos antiSkidSw("ANTI_SKID_SW", antiskidPin);
DcsBios::Switch2Pos hookBypassSw("HOOK_BYPASS_SW", hookBypassPin);

//DcsBios::Switch2Pos emergencyParkingBrakePull("EMERGENCY_PARKING_BRAKE_PULL", parkingBPullPin);
//DcsBios::Switch3Pos emergencyParkingBrakeRotate("EMERGENCY_PARKING_BRAKE_ROTATE", parkingRot1Pin, parkingRot2Pin);

void setup() {
  DcsBios::setup();
  /*Set Switch Pins to Inputs and Mag Pins to Outputs
    for (int i=0;i<NUMBUTTONS;i++){
      pinMode(SwitchOnPin[i], INPUT_PULLUP);
    }
  // Initialize Joystick Library
  Joystick.begin();*/
}

void loop() {
  DcsBios::loop();
  /*for (int i=0;i<NUMBUTTONS;i++)
  {
    int btnState = !digitalRead(SwitchOnPin[i]);
    if (btnState != lastBtnState[i])
    {
      Joystick.setButton(i, btnState);
      lastBtnState[i] = btnState;
    }
  }
 
  delay(50);*/
}