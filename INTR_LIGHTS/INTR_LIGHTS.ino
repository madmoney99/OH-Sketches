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


/*** @file INTR_LIGHTS.ino>
/** @author <Tony Goodale>
 * @date <Dec 8-22>
 * @brief <INTR LIGHT DCS BIOS sketch in line with the OpenHornet Interconnect dated 2022-08-05>
 *
 * <Put a more detailed description of the sketch here>
 */

#define DCSBIOS_DEFAULT_SERIAL

#include "DcsBios.h"
#define chartDimmerPin A1
#define warnCautionDimmerPin A2
#define lightsTestSwPin A3
#define cockkpitLightModeSwPinA 2
#define cockkpitLightModeSwPinB 3
#define consolesDimmerPin A7
#define instPnlDimmerPin A8
#define floodDimmerPin A10

/* paste code snippets from the reference documentation here */
DcsBios::PotentiometerEWMA<5, 128, 50> chartDimmer("CHART_DIMMER", chartDimmerPin);
DcsBios::PotentiometerEWMA<5, 128, 50> warnCautionDimmer("WARN_CAUTION_DIMMER", warnCautionDimmerPin);
DcsBios::Switch2Pos lightsTestSw("LIGHTS_TEST_SW", lightsTestSwPin, true);
DcsBios::Switch3Pos cockkpitLightModeSw("COCKKPIT_LIGHT_MODE_SW", cockkpitLightModeSwPinA, cockkpitLightModeSwPinB);
DcsBios::PotentiometerEWMA<5, 128, 50> consolesDimmer("CONSOLES_DIMMER", consolesDimmerPin);
DcsBios::PotentiometerEWMA<5, 128, 50> instPnlDimmer("INST_PNL_DIMMER", instPnlDimmerPin);
DcsBios::PotentiometerEWMA<5, 128, 50> floodDimmer("FLOOD_DIMMER", floodDimmerPin);

void setup() {
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}

