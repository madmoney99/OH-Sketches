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


/*** @file COMM_PANEL.ino>
/** @author <Tony Goodale>
 * @date <Dec 18-22>
 * @brief <COMM PANEL DCS BIOS sketch in line with the OpenHornet Interconnect dated 2022-08-05>
 *
 * <No ILS switch>
 * 
 */

#define DCSBIOS_DEFAULT_SERIAL

#include <DcsBios.h>

/* paste code snippets from the reference documentation here */
/*POTS*/
DcsBios::Potentiometer comVox("COM_VOX", A0);
DcsBios::Potentiometer comIcs("COM_ICS", A15);
DcsBios::Potentiometer comRwr("COM_RWR", A1);
DcsBios::Potentiometer comWpn("COM_WPN", A14);
DcsBios::Potentiometer comMidsB("COM_MIDS_B", A2);
DcsBios::Potentiometer comMidsA("COM_MIDS_A", A13);
DcsBios::Potentiometer comTacan("COM_TACAN", A3);
DcsBios::Potentiometer comAux("COM_AUX", A12);


/*SWITCHES*/
DcsBios::Switch3Pos comCommRelaySw("COM_COMM_RELAY_SW", 52, 53);
DcsBios::Switch3Pos comCommGXmtSw("COM_COMM_G_XMT_SW", 50, 51);
DcsBios::Switch2Pos comIlsUfcManSw("COM_ILS_UFC_MAN_SW", 48, true);
DcsBios::Switch3Pos comCryptoSw("COM_CRYPTO_SW", 49, 46);
DcsBios::Switch3Pos comIffMode4Sw("COM_IFF_MODE4_SW", 44, 45);
DcsBios::Switch2Pos comIffMasterSw("COM_IFF_MASTER_SW", 47);

DcsBios::Switch3Pos comm1AntSelectSw("COMM1_ANT_SELECT_SW", PIN0, 41);
DcsBios::Switch3Pos iffAntSelectSw("IFF_ANT_SELECT_SW", PIN1, 38);

/*NOT IN SERVICE YET
const byte comIlsChannelSwPins[20] = {PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7, PIN_8, PIN_9, PIN_10, PIN_11, PIN_12, PIN_13, PIN_14, PIN_15, PIN_16, PIN_17, PIN_18, PIN_19};
DcsBios::SwitchMultiPos comIlsChannelSw("COM_ILS_CHANNEL_SW", comIlsChannelSwPins, 20);*/

void setup() {
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}





























