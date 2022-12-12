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


/*** @file IFEI_PANEL.ino>
/** @author <Tony Goodale>
 * @date <Dec 11-22>
 * @brief <IFEI_PANEL DCS BIOS>
 * NON STANDARD
 * Missing JETT SELECT RI, RO, LI, LO, CTR as there is a Tekcreationz panel there.
 * 
 */

#define DCSBIOS_DEFAULT_SERIAL

#include "DcsBios.h"

/* paste code snippets from the reference documentation here */
DcsBios::Switch2Pos ifeiUpBtn("IFEI_UP_BTN", 2);
DcsBios::Switch2Pos ifeiQtyBtn("IFEI_QTY_BTN", 3);
DcsBios::Switch2Pos ifeiModeBtn("IFEI_MODE_BTN", 4);

DcsBios::Switch2Pos ifeiDwnBtn("IFEI_DWN_BTN", 7);
DcsBios::Switch2Pos ifeiZoneBtn("IFEI_ZONE_BTN", 8);
DcsBios::Switch2Pos ifeiEtBtn("IFEI_ET_BTN", 9);

DcsBios::PotentiometerEWMA<5, 128, 50> ifei("IFEI", A3);
DcsBios::Switch3Pos modeSelectorSw("MODE_SELECTOR_SW", 15, 14);
DcsBios::Switch3Pos selectHudLddiRddi("SELECT_HUD_LDDI_RDDI", A10, 16);


void setup() {
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}