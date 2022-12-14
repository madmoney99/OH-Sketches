

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


/*** @file FCS_PANEL.ino>
/** @author <Tony Goodale>
 * @date <Dec 9-22>
 * @brief <FCS PANEL DCS BIOS sketch in line with the OpenHornet Interconnect dated 2022-08-05>
 *
 *Changes from OH Standard:
  Gain switch not working in ORIDE pos
  trim POT was replaced with a rotary encoder with button press on top.
 * 
 */

#define DCSBIOS_DEFAULT_SERIAL

#include <DcsBios.h>

/* paste code snippets from the reference documentation here */
DcsBios::RotaryEncoder rudTrim("RUD_TRIM", "-400", "+400", A3, 4);
DcsBios::Switch2Pos toTrimBtn("TO_TRIM_BTN", 2);
DcsBios::Switch2Pos fcsResetBtn("FCS_RESET_BTN", A2);
DcsBios::Switch2Pos gainSwitchCover("GAIN_SWITCH_COVER", 15, true);
DcsBios::Switch2Pos gainSwitch("GAIN_SWITCH", 14, true);

void setup() {
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}