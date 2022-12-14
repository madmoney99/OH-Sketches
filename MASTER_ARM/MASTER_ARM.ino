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


/*** @file MASTER_PANEL.ino>
/** @author <Tony Goodale>
 * @date <Dec 11-22>
 * @brief <MASTER_PANEL DCS BIOS>
 *
 *
 * 
 */

#define DCSBIOS_DEFAULT_SERIAL

#include <DcsBios.h>

/* paste code snippets from the reference documentation here */
DcsBios::Switch2Pos fireExtBtn("FIRE_EXT_BTN", A3);
DcsBios::Switch2Pos masterModeAg("MASTER_MODE_AG", A2);
DcsBios::Switch2Pos emerJettBtn("EMER_JETT_BTN", A1);
DcsBios::Switch2Pos masterModeAa("MASTER_MODE_AA", 2);
DcsBios::Switch2Pos masterArmSw("MASTER_ARM_SW", 3);


/*To be sorted out, backlighting?
DcsBios::LED mcReady(0x740c, 0x8000, A3);
DcsBios::LED masterModeAaLt(0x740c, 0x0200, PIN);
DcsBios::LED masterModeAgLt(0x740c, 0x0400, PIN);
DcsBios::LED mcDisch(0x740c, 0x4000, PIN);

*/

void setup() {
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}