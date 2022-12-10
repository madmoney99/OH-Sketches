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


/*** @file KY58_PANEL.ino>
/** @author <Tony Goodale>
 * @date <Dec 9-22>
 * @brief <KY58 PANEL DCS BIOS sketch in line with the OpenHornet Interconnect dated 2022-08-05>
 *
 * <Put a more detailed description of the sketch here>
 * 
 */

#define DCSBIOS_DEFAULT_SERIAL

#include "DcsBios.h"

/* paste code snippets from the reference documentation here */
const byte ky58ModeSelectPins[7] = {A3, 2, A2, 3}
;DcsBios::SwitchMultiPos ky58ModeSelect("KY58_MODE_SELECT", ky58ModeSelectPins, 7);
DcsBios::Switch3Pos ky58PowerSelect("KY58_POWER_SELECT", A1, 4);
DcsBios::PotentiometerEWMA<5, 128, 50> ky58Volume("KY58_VOLUME", A0);
const byte ky58FillSelectPins[15] = {15, 6, 14, 7, 16, 8, 10, 9}
;DcsBios::SwitchMultiPos ky58FillSelect("KY58_FILL_SELECT", ky58FillSelectPins, 15);

void setup() {
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}