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


/*** @file HID_INTR_LIGHTS.ino>
/** @author <Tony Goodale>
 * @date <Dec 8-22>
 * @brief <HID_INTR LIGHT DCS BIOS sketch in line with the OpenHornet Interconnect dated 2022-08-05>
 *
 * <Put a more detailed description of the sketch here>
 */

#define DCSBIOS_DEFAULT_SERIAL

#include <DcsBios.h>

//HID Panel for ECS PANEL
#include <Joystick.h>
#define NUMBUTTONS 3
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
  NUMBUTTONS, 0,                  // Button Count, Hat Switch Count
  true, true, true,     // X and Y, but no Z Axis
  true, true, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

int xAxis = A7;
int yAxis = A8;
int zAxis = A10;
int rxAxis = A1;
int ryAxis = A2;
int xAxisValue = 0;
int yAxisValue = 0;
int zAxisValue = 0;
int rxAxisValue = 0;
int ryAxisValue = 0;

/* paste code snippets from the reference documentation here */
DcsBios::Potentiometer chartDimmer("CHART_DIMMER", A1);
DcsBios::Potentiometer warnCautionDimmer("WARN_CAUTION_DIMMER", A2);
DcsBios::Switch2Pos lightsTestSw("LIGHTS_TEST_SW", A3, true);
DcsBios::Switch3Pos cockkpitLightModeSw("COCKKPIT_LIGHT_MODE_SW", 2, 3);
DcsBios::Potentiometer consolesDimmer("CONSOLES_DIMMER", A7);
DcsBios::Potentiometer instPnlDimmer("INST_PNL_DIMMER", A8);
DcsBios::Potentiometer floodDimmer("FLOOD_DIMMER", A10);

void setup() {
  DcsBios::setup();
  // Set Range Values
  Joystick.setXAxisRange(0,1024);
  Joystick.setYAxisRange(0,1024);
  Joystick.setZAxisRange(0,1024);
  Joystick.setRxAxisRange(0,1024);
  Joystick.setRyAxisRange(0,1024);
  // Initialize Button Pins
  pinMode(A3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  // Initialize Joystick Library
  Joystick.begin();
}

// defining the total [#] of buttons and their pins
const int ButtonToPinMap[NUMBUTTONS] = {A3,2,3};
int lastButtonState[NUMBUTTONS] = {0,0,0};

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
  zAxisValue = analogRead(zAxis);
  Joystick.setZAxis(zAxisValue);
  delay(1); 
  rxAxisValue = analogRead(rxAxis);
  Joystick.setRxAxis(rxAxisValue);
  delay(1); 
  ryAxisValue = analogRead(ryAxis);
  Joystick.setRyAxis(ryAxisValue);
  delay(1); 

}

