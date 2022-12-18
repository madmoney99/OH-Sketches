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


/*** @file APU_PANEL.ino>
/** @author <Tony Goodale>
 * @date <Dec 9-22>
 * @brief <APU PANEL DCS BIOS sketch in line with the OpenHornet Interconnect dated 2022-08-05>
 *
 * <No Mag switch, relay or circuit breakers set up yet.>
 * 
 */

#define DCSBIOS_DEFAULT_SERIAL

#include <DcsBios.h>
//Setup the DDI Buttons - Use library from @Balse on Discord - https://github.com/balzreber/TCA9534
#include <TCA9534.h>

TCA9534 ampcdButtons[4] = {
  TCA9534(0x23), //Left Row
  TCA9534(0x20), //Top Row
  TCA9534(0x22), //Right Row
  TCA9534(0x21)  //Bottom Row
};
bool lastBtnState[28];
bool buttonState[28];
uint8_t inputRegister[4];
unsigned long lastDebounceTime[28];
unsigned long debounceDelay = 10;    // the debounce time; increase if the output flickers
int index; 
char *AMPCD_Btns[] = {"AMPCD_GAIN_SW",
"AMPCD_NIGHT_DAY",
"AMPCD_SYM_SW",
"AMPCD_CONT_SW"};
char btnName[20];

void onInstPnlDimmerChange(unsigned int newValue) {
    analogWrite(6,map(newValue,0,65535,0,100));
}

/* paste code snippets from the reference documentation here */
DcsBios::Switch3Pos leftDdiCrsSw("LEFT_DDI_CRS_SW", 4, 7);
DcsBios::Switch3Pos leftDdiHdgSw("LEFT_DDI_HDG_SW", 8, 10);

void setup() {
  DcsBios::setup();
  pinMode(6, OUTPUT);


  for (int i = 0; i < sizeof(lastBtnState) / sizeof(lastBtnState[0]); i++) {
    lastBtnState[i] = 0;
  }
  for (int i = 0; i < sizeof(ampcdButtons) / sizeof(ampcdButtons[0]); i++) {
    ampcdButtons[i].Begin();
    for (int j = 0; j < 7; j++) {
      ampcdButtons[i].PinMode(j, INPUT);
    }
  }
analogWrite(6,75);
}

void loop() {
  DcsBios::loop();

  for (int i = 0; i < sizeof(ampcdButtons) / sizeof(ampcdButtons[0]); i++) {
    inputRegister[i] = ampcdButtons[i].ReadAll();
    // i == 0; Left
    // i == 1; Top - Reversed (DDI v2)
    // i == 2; Right - Reversed (DDI v2)
    // i == 3; Bottom

    for (int j = 0; j < 5; j++) {
      int index; 
      if(i== 1 || i == 2){
         index = ((4-j) + 5 * i);
      }else{
         index = (j + 5 * i);
      }
      

      bool btnState = (inputRegister[i] >> (4 - j)) & 1;

      if(btnState != lastBtnState[index]) {
        lastDebounceTime[index] = millis();
      }

      if ((millis() - lastDebounceTime[index]) > debounceDelay) {
        if (btnState != buttonState[index]) {
            buttonState[index] = btnState;
                  char btnName[15];
                  sprintf(btnName, "AMPCD_PB_%02d", index + 1);
                  DcsBios::tryToSendDcsBiosMessage(btnName, btnState == 1 ? "0" : "1");
        }
      }
      lastBtnState[index] = btnState;
    }
    
    
  }
}