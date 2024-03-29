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


/*** @file HID_DISP_ECM_PANEL.ino>
/** @author <Tony Goodale>
 * @date <Dec 30-22>
 * @brief <HID_DISP_ECM DCS BIOS>
 *
 *
 * 
 */

#define DCSBIOS_DEFAULT_SERIAL

#include <DcsBios.h>
//HID Panel for ECM PANEL
#include <Joystick.h>
Joystick_ Joystick;

/* paste code snippets from the reference documentation here */
DcsBios::Switch2Pos cmsdJetSelBtn("CMSD_JET_SEL_BTN", 15);
const byte ecmModeSwPins[5] = {4, 6, 14, 7, 16};
DcsBios::SwitchMultiPos ecmModeSw("ECM_MODE_SW", ecmModeSwPins, 5);
DcsBios::Switch3Pos cmsdDispenseSw("CMSD_DISPENSE_SW", 8, 10);
DcsBios::Switch2Pos auxRelSw("AUX_REL_SW", 9);

void setup() {
  DcsBios::setup();
  // Initialize Button Pins
  pinMode(15, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  // Initialize Joystick Library
  Joystick.begin();
}

// defining the total [#] of buttons and their pins
#define NUMBUTTONS 9
const int ButtonToPinMap[NUMBUTTONS] = {15,4,6,14,7,16,8,10,9};
int lastButtonState[NUMBUTTONS] = {0,0,0,0,0,0,0,0,0};

void loop() {
  DcsBios::loop();
  for (int index = 0; index < NUMBUTTONS; index++)
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