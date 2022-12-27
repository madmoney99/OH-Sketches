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


/*** @file HID_SNSR_PANEL.ino>
/** @author <Tony Goodale>
 * @date <Dec 26-22>
 * @brief <HID_SNSR_PANEL DCS BIOS sketch in line with the OpenHornet Interconnect dated 2022-08-05>
 *
 * <Put a more detailed description of the sketch here>
 * 
 */

#define DCSBIOS_DEFAULT_SERIAL

#include <DcsBios.h>
//HID Panel for SNSR PANEL
#include <Joystick.h>
Joystick_ Joystick;

/* paste code snippets from the reference documentation here */
DcsBios::Switch3Pos flirSw("FLIR_SW", A3, A2);
DcsBios::Switch2Pos ltdRSw("LTD_R_SW", 3);
DcsBios::Switch2Pos lstNflrSw("LST_NFLR_SW", 15);
const byte radarSwPins[4] = {PIN0 , A1, 4, A0 };
DcsBios::SwitchMultiPos radarSw("RADAR_SW", radarSwPins, 4);
const byte insSwPins[8] = { 2, 6, 14, 7, 16, 8, 10, 9 };
DcsBios::SwitchMultiPos insSw("INS_SW", insSwPins, 8);

void setup() {
  DcsBios::setup();
  // Initialize Button Pins
  pinMode(A3, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
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
#define numberOfButtons 15
const int ButtonToPinMap[numberOfButtons] = {A3,A2,3,15,A1,4,A0,2,6,14,7,16,8,10,9};
int lastButtonState[numberOfButtons] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

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