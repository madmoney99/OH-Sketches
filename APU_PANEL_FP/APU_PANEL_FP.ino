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


/*** @file APU_PANEL.ino>
/** @author <Tony Goodale>
 * @date <Dec 9-22>
 * @brief <APU PANEL DCS BIOS sketch in line with the OpenHornet Interconnect dated 2022-08-05>
 *
 * <No Mag switch, relay or circuit breakers set up yet.>
 * 
 */

#define DCSBIOS_DEFAULT_SERIAL

#include <DcsBios.h>

//HID Panel for APU PANEL

#include <Joystick.h>

Joystick_ Joystick;


/* paste code snippets from the reference documentation here */
DcsBios::Switch2Pos apuControlSw("APU_CONTROL_SW", 15, true);
DcsBios::LED apuReadyLt(0x74bc, 0x0400, 6);
DcsBios::Switch3Pos engineCrankSw("ENGINE_CRANK_SW", 14, 7);

void setup() {
  DcsBios::setup();
  // Initialize Button Pins
  pinMode(14, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  // Initialize Joystick Library
  Joystick.begin();
}
// defining the total [#] of buttons and their pins
const int ButtonToPinMap[2] = {4,7};

int lastButtonState[2] = {0,0};
void loop() {
  DcsBios::loop();

  for (int index = 0; index < 15; index++)
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