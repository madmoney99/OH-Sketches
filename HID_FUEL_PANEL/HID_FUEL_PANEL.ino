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


/*** @file HID_FUEL_PANEL.ino>
/** @author <Tony Goodale>
 * @date <Dec 26-22>
 * @brief <HID_FUEL_PANEL DCS BIOS sketch in line with the OpenHornet Interconnect dated 2022-08-05>
 *
 * <Put a more detailed description of the sketch here>
 * 
 */

#define DCSBIOS_DEFAULT_SERIAL

#include <DcsBios.h>
//HID Panel for FUEL PANEL
#include <Joystick.h>
Joystick_ Joystick;

/* paste code snippets from the reference documentation here */
DcsBios::Switch3Pos probeSw("PROBE_SW", 15, 6);
DcsBios::Switch3Pos extWngTankSw("EXT_WNG_TANK_SW", 14, 7);
DcsBios::Switch3Pos extCntTankSw("EXT_CNT_TANK_SW", 16, 8);
DcsBios::Switch2Pos fuelDumpSw("FUEL_DUMP_SW", 10, true);


void setup() {
  DcsBios::setup();
  // Initialize Button Pins
  pinMode(15, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  // Initialize Joystick Library
  Joystick.begin();
}

// defining the total [#] of buttons and their pins
#define numberOfButtons 7
const int ButtonToPinMap[numberOfButtons] = {15,14,16,6,7,8,10};
int lastButtonState[numberOfButtons] = {0,0,0,0,0,0,0};

void loop() {
  DcsBios::loop();
  for (int index = 0; index < numberOfButtons; index++)
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