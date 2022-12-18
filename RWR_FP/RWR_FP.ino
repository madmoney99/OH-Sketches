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


/*** @file RWR_PANEL.ino>
/** @author <Tony Goodale>
 * @date <Dec 11-22>
 * @brief <RWR_PANEL DCS BIOS>
 *
 *
 * 
 */

#define DCSBIOS_DEFAULT_SERIAL

#include <DcsBios.h>

/* paste code snippets from the reference documentation here */
/* FROM BOARD*/
DcsBios::Potentiometer rwrAudioCtrl("RWR_AUDIO_CTRL", A3);
DcsBios::Potentiometer rwrDmrCtrl("RWR_DMR_CTRL", A2);
DcsBios::ActionButton rwrSpecialBtnToggle("RWR_SPECIAL_BTN", "TOGGLE", A1);
DcsBios::ActionButton rwrBitBtnToggle("RWR_BIT_BTN", "TOGGLE", A0);

DcsBios::ActionButton rwrPowerBtnToggle("RWR_POWER_BTN", "TOGGLE", 2);
DcsBios::Switch2Pos rwrLimitBtn("RWR_LIMIT_SW", 3);
DcsBios::ActionButton rwrOffsetBtnToggle("RWR_OFFSET_BTN", "TOGGLE", 4);
const byte rwrDisTypeSwPins[5] = {15, 6, 14, 7, 16};
DcsBios::SwitchMultiPos rwrDisTypeSw("RWR_DIS_TYPE_SW", rwrDisTypeSwPins, 5);

void setup() {
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}