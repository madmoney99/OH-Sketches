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


/*** @file HID_ECS_PANEL.ino>
/** @author <Tony Goodale>
 * @date <Dec 30-22>
 * @brief <HID_ECS_PANEL PANEL DCS BIOS sketch in line with the OpenHornet Interconnect dated 2022-08-05>
 *
 * <Put a more detailed description of the sketch here>
 * 
 */

#define DCSBIOS_DEFAULT_SERIAL
#include <DcsBios.h>

//HID Panel for ECS PANEL
#include <Joystick.h>
#define NUMBUTTONS 7
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
  NUMBUTTONS, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

int xAxis = A9;
int yAxis = A10;
int xAxisValue = 0;
int yAxisValue = 0;

/* paste code snippets from the reference documentation here */
/* BLEED AIR SWITCH NOT DONE YET
DcsBios::Switch2Pos bleedAirPull("BLEED_AIR_PULL", PIN);
const byte bleedAirKnobPins[7] = {PIN_0, PIN_1, PIN_2, PIN_3}
;DcsBios::SwitchMultiPos bleedAirKnob("BLEED_AIR_KNOB", bleedAirKnobPins, 7);
*/
DcsBios::Switch3Pos ecsModeSw("ECS_MODE_SW", A3, A2);
DcsBios::Switch3Pos cabinPressSw("CABIN_PRESS_SW", A1, 4);

DcsBios::Switch2Pos pitotHeatSw("PITOT_HEAT_SW", A0, true);
DcsBios::Switch3Pos engAntiiceSw("ENG_ANTIICE_SW", 15, 6);

DcsBios::Potentiometer cabinTemp("CABIN_TEMP", A9);
DcsBios::Potentiometer suitTemp("SUIT_TEMP", A10);

void setup() {
  DcsBios::setup();
  // Set Range Values
  Joystick.setXAxisRange(0,1024);
  Joystick.setYAxisRange(0,1024);
  // Initialize Button Pins
  pinMode(A3, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  // Initialize Joystick Library
  Joystick.begin();
}

// defining the total [#] of buttons and their pins
const int ButtonToPinMap[NUMBUTTONS] = {A3,A2,A1,4,A0,15,6};
int lastButtonState[NUMBUTTONS] = {0,0,0,0,0,0,0};

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

  xAxisValue = analogRead(xAxis);
  Joystick.setXAxis(xAxisValue);
  delay(1);

  yAxisValue = analogRead(yAxis);
  Joystick.setYAxis(yAxisValue);
  delay(1); 

}