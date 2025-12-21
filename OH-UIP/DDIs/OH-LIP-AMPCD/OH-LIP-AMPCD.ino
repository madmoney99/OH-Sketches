

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

/**
 * @file <AMPCD.ino>
 * @author <Tony Goodale> 
 * @date <2023-3-13>
 * @brief <Arduino ProMicro Code for AMPCD Controller>
 * adapted from Peter Sawka's original Nano code
 */

// DCS Bios Configuration - No RS458 Communcation
#define DCSBIOS_DEFAULT_SERIAL

// DCS-BIOS Configuration for RS485
//#define DCSBIOS_RS485_SLAVE 3
//#define TXENABLE_PIN 2

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

void onConsoleIntLtChange(unsigned int newValue) {
      analogWrite(9,  map(newValue, 0, 65535, 0, 255));
}

DcsBios::IntegerBuffer consoleIntLtBuffer(0x7558, 0xffff, 0, onConsoleIntLtChange);
DcsBios::Potentiometer ampcdBrtCtl("AMPCD_BRT_CTL", A0);

DcsBios::Switch3Pos leftDdiCrsSw("LEFT_DDI_CRS_SW", 4, 7);
DcsBios::Switch3Pos leftDdiHdgSw("LEFT_DDI_HDG_SW", 8, 10);

/**
* Arduino Setup Function
* 
* Arduino standard Setup Function. Code who should be executed
* only once at the programm start, belongs in this function.
*/
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

/**
* Arduino Loop Function
* 
* Arduino standard Loop Function. Code who should be executed
* over and over in a loop, belongs in this function.
*/
void loop() {
  DcsBios::loop();
  
  for (int i = 0; i < sizeof(ampcdButtons) / sizeof(ampcdButtons[0]); i++) {
    inputRegister[i] = ampcdButtons[i].ReadAll();

    for (int j = 0; j < 7; j++) {
      
      index = j+(7*i);

      bool btnState = (inputRegister[i] >> (6 - j)) & 1;

      if(btnState != lastBtnState[index]) {
        lastDebounceTime[index] = millis();
      }

      if ((millis() - lastDebounceTime[index]) > debounceDelay) {
        if (btnState != buttonState[index]) {
          buttonState[index] = btnState;
          if (j>4){
            if(btnState!=1){
              if (i==0 or i==1){
                if(j==5){ DcsBios::tryToSendDcsBiosMessage(AMPCD_Btns[i], "2"); }
                if(j==6){ DcsBios::tryToSendDcsBiosMessage(AMPCD_Btns[i], "0"); } 
              }else {
                if(j==5){ DcsBios::tryToSendDcsBiosMessage(AMPCD_Btns[i], "0"); }
                if(j==6){ DcsBios::tryToSendDcsBiosMessage(AMPCD_Btns[i], "2"); } 
              }
            }else{
              DcsBios::tryToSendDcsBiosMessage(AMPCD_Btns[i], "1");
            }
          }else{
            int btnNum = 4-j+5*i;
            sprintf(btnName, "AMPCD_PB_%02d", btnNum + 1);
            DcsBios::tryToSendDcsBiosMessage(btnName, btnState == 1 ? "0" : "1");
          }
        }
      }
      lastBtnState[index] = btnState;
    }  
  }
}
