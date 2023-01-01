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


/*** @file IFEI_PANEL.ino>
/** @author <Tony Goodale>
 * @date <Dec 11-22>
 * @brief <IFEI_PANEL DCS BIOS>
 * NON STANDARD
 * Missing JETT SELECT RI, RO, LI, LO, CTR as there is a Tekcreationz panel there.
 * 
 */

#define DCSBIOS_DEFAULT_SERIAL

#include <DcsBios.h>
#include <Joystick.h>
//HID Panel for APU PANEL
#define NUMBUTTONS 10
//Declare Pins
#define upPin 2
#define qtyPin 3
#define modePin 4
#define downPin 7
#define zonePin 8
#define etPin 9
#define selectPin1 15
#define selectPin2 14
#define dddiPin1 A10
#define dddiPin2 16
int SwitchOnPin[NUMBUTTONS] = {modePin,qtyPin,upPin,downPin,zonePin,etPin,dddiPin1,dddiPin2,selectPin2,selectPin1};
//Store States
bool lastBtnState[NUMBUTTONS] = {0,0,0,0,0,0,0,0,0,0};
bool btnState[NUMBUTTONS] = {0,0,0,0,0,0,0,0,0,0};

int xAxis = A3;
int xAxisValue = 0;

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
  NUMBUTTONS, 0,                  // Button Count, Hat Switch Count
  true, false, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

/* paste code snippets from the reference documentation here */
DcsBios::Switch2Pos ifeiUpBtn("IFEI_UP_BTN", upPin);
DcsBios::Switch2Pos ifeiQtyBtn("IFEI_QTY_BTN", qtyPin);
DcsBios::Switch2Pos ifeiModeBtn("IFEI_MODE_BTN", modePin);

DcsBios::Switch2Pos ifeiDwnBtn("IFEI_DWN_BTN", downPin);
DcsBios::Switch2Pos ifeiZoneBtn("IFEI_ZONE_BTN", zonePin);
DcsBios::Switch2Pos ifeiEtBtn("IFEI_ET_BTN", etPin);

DcsBios::PotentiometerEWMA<5, 128, 50> ifei("IFEI", A3);
DcsBios::Switch3Pos modeSelectorSw("MODE_SELECTOR_SW", selectPin1, selectPin2);
DcsBios::Switch3Pos selectHudLddiRddi("SELECT_HUD_LDDI_RDDI", dddiPin1, dddiPin2);


void setup() {
  DcsBios::setup();
  // Set Range Values
  Joystick.setXAxisRange(0,1024);
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

}