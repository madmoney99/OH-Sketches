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


/*** @file HID_HUD_PANEL.ino>
/** @author <Tony Goodale>
 * @date <Jan 18-23>
 * @brief <HID_HUD_PANEL PANEL DCS BIOS sketch in line with the OpenHornet Interconnect dated 2022-08-05>
 *
 * <Put a more detailed description of the sketch here>
 * 
 */

#define DCSBIOS_DEFAULT_SERIAL
#include <DcsBios.h>

//HID Panel for ECS PANEL
#include <Joystick.h>
#define NUMBUTTONS 8
//Declare Pins
#define brtPot A3
#define blkPot A2
#define balPot A1
#define aoaPot A0
#define rejNormPin 15
#define rej2Pin 6
#define dayPin 14
#define wbWBPin 7
#define wbOFFPin 16
#define altBAROPin 8
#define attINSPin 10
#define attSTBYPin 9

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
  NUMBUTTONS, 0,                  // Button Count, Hat Switch Count
  true, true, true,     // X and Y, but no Z Axis
  true, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

int xAxis = A3;
int yAxis = A2;
int zAxis = A1;
int rxAxis = A0;
int xAxisValue = 0;
int yAxisValue = 0;
int zAxisValue = 0;
int rxAxisValue = 0;

// defining the total [#] of buttons and their pins
int SwitchOnPin[NUMBUTTONS] = {rejNormPin,rej2Pin,dayPin,wbWBPin,wbOFFPin,altBAROPin,attINSPin,attSTBYPin};
bool lastBtnState[NUMBUTTONS] = {0,0,0,0,0,0,0,0};
bool btnState[NUMBUTTONS] = {0,0,0,0,0,0,0,0};

/* paste code snippets from the reference documentation here */
DcsBios::Switch3Pos hudSymRejSw("HUD_SYM_REJ_SW", rejNormPin, rej2Pin);
DcsBios::Switch2Pos hudSymBrtSelect("HUD_SYM_BRT_SELECT", dayPin);
DcsBios::Switch3Pos hudVideoControlSw("HUD_VIDEO_CONTROL_SW", wbWBPin, wbOFFPin);
DcsBios::Switch2Pos hudAltSw("HUD_ALT_SW", altBAROPin);
DcsBios::Switch3Pos hudAttSw("HUD_ATT_SW", attINSPin, attSTBYPin);

DcsBios::Potentiometer hudSymBrt("HUD_SYM_BRT", brtPot);
DcsBios::Potentiometer hudBlackLvl("HUD_BLACK_LVL", blkPot);
DcsBios::Potentiometer hudBalance("HUD_BALANCE", balPot);
DcsBios::Potentiometer hudAoaIndexer("HUD_AOA_INDEXER", aoaPot);

void setup() {
  DcsBios::setup();
  // Set Range Values
  Joystick.setXAxisRange(0,1024);
  Joystick.setYAxisRange(0,1024);
  Joystick.setZAxisRange(0,1024);
  Joystick.setRxAxisRange(0,1024);
  //Set Switch Pins to Inputs
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

  xAxisValue = analogRead(xAxis);
  Joystick.setXAxis(xAxisValue);
  delay(1);
  yAxisValue = analogRead(yAxis);
  Joystick.setYAxis(yAxisValue);
  delay(1); 
  zAxisValue = analogRead(zAxis);
  Joystick.setZAxis(zAxisValue);
  delay(1); 
  rxAxisValue = analogRead(rxAxis);
  Joystick.setRxAxis(rxAxisValue);
  delay(1); 
}

