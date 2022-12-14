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
 * @file <Left_DDI.ino>
 * @author <@petersawka> <@dnamaster2000>
 * @date <2021-10-11>
 * @brief <Arduino Nano Code for Left DDI Controller>
 */

// DCS Bios Configuration - No RS485 Communcation
#define DCSBIOS_DEFAULT_SERIAL

// DCS-BIOS Configuration for RS485
//define DCSBIOS_RS485_SLAVE 2 //Set Correct Slave Number based on your configuration
#define TXENABLE_PIN 3 

#include "DcsBios.h" 

//Setup the DDI Buttons - Use library from @Balse on Discord - https://github.com/balzreber/TCA9534
#include "TCA9534.h"


TCA9534 ddiButtons[4] = {
  TCA9534(0x23), //Left Row
  TCA9534(0x20), //Top Row
  TCA9534(0x22), //Right Row
  TCA9534(0x21)  //Bottom Row
};

bool lastBtnState[20];
bool buttonState[20];
uint8_t inputRegister[4];
unsigned long lastDebounceTime[20];
unsigned long debounceDelay = 10;    // the debounce time; increase if the output flickers

void onInstPnlDimmerChange(unsigned int newValue) {
    analogWrite(6,map(newValue,0,65535,0,255));
}
DcsBios::IntegerBuffer instPnlDimmerBuffer(0x7546, 0xffff, 0, onInstPnlDimmerChange);

DcsBios::RotaryEncoder leftDdiBrtCtl("RIGHT_DDI_BRT_CTL", "-500", "+500", A0, A1);
DcsBios::RotaryEncoder leftDdiContCtl("RIGHT_DDI_CONT_CTL", "-500", "+500", A2, A3);

const byte leftDdiBrtSelectPins[3] = {10, 11, 12};
DcsBios::SwitchMultiPos leftDdiBrtSelect("RIGHT_DDI_BRT_SELECT", leftDdiBrtSelectPins, 3);

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
  for (int i = 0; i < sizeof(ddiButtons) / sizeof(ddiButtons[0]); i++) {
    ddiButtons[i].Begin();
    for (int j = 0; j < 5; j++) {
      ddiButtons[i].PinMode(j, INPUT);
    }
    /*
    for (int j = 5; j < 5; j++) {
      ddiButtons[i].PinMode(j, OUTPUT);
    }
    */
  }
}

/**
* Arduino Loop Function
* 
* Arduino standard Loop Function. Code who should be executed
* over and over in a loop, belongs in this function.
*/
void loop() {
  DcsBios::loop();

  for (int i = 0; i < sizeof(ddiButtons) / sizeof(ddiButtons[0]); i++) {
    inputRegister[i] = ddiButtons[i].ReadAll();
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
                  char btnName[14];
                  sprintf(btnName, "RIGHT_DDI_PB_%02d", index + 1);
                  DcsBios::tryToSendDcsBiosMessage(btnName, btnState == 1 ? "0" : "1");
        }
      }
      lastBtnState[index] = btnState;
    }
    
    
  }
}
