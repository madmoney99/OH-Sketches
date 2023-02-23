
/*** @file ButtonBox1.ino>
/** @author <Tony Goodale>
 * @date <Feb 22-23>
 * @brief <HID_Button Box Build 1>
 *
 * 
 */

//HID Panel for Button Box Build 1
#include <Joystick.h>
#include <Keypad.h>
#define ENABLE_PULLUPS // Enable Pull-ups for switches
#define NUMBUTTONS 31
#define NUMROTARIES 2
#define NUMROWS 5 // Rows 
#define NUMCOLS 6 // Columns 
byte rowPins [NUMROWS] = {10,16,14,15,A0};
byte colPins [NUMCOLS] = {4,5,6,7,8,9};
byte buttons [NUMROWS] [NUMCOLS] = {
{5,6,7,8,9,10},
{11,12,13,14,15,16},
{17,18,19,20,21,22},
{23,24,25,26,27,28},
{29,30,31,32,33,34}
};

Keypad buttbx = Keypad( makeKeymap(buttons), rowPins, colPins, NUMROWS, NUMCOLS);
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
  NUMBUTTONS, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

struct rotariesdef {
  byte pin1;
  byte pin2;
  int ccwchar;
  int cwchar;
  volatile unsigned char state;
};

//ROTARY ENCODERS
//each line controls a different rotary encoder
//the first two numbers refer to the pins the encoder is connected to
//the second two are the buttons each click of the encoder wil press
//do NOT exceed 31 for the final button number
rotariesdef rotaries[NUMROTARIES] {
  {1, 0, 29, 30, 0}, //rotary 1
  {2, 3, 7, 23, 0}, //rotary 2
};

#define DIR_CCW 0x10
#define DIR_CW 0x20
#define R_START 0x0

#ifdef HALF_STEP
#define R_CCW_BEGIN 0x1
#define R_CW_BEGIN 0x2
#define R_START_M 0x3
#define R_CW_BEGIN_M 0x4
#define R_CCW_BEGIN_M 0x5
const unsigned char ttable[6][4] = {
  // R_START (00)
  {R_START_M,            R_CW_BEGIN,     R_CCW_BEGIN,  R_START},
  // R_CCW_BEGIN
  {R_START_M | DIR_CCW, R_START,        R_CCW_BEGIN,  R_START},
  // R_CW_BEGIN
  {R_START_M | DIR_CW,  R_CW_BEGIN,     R_START,      R_START},
  // R_START_M (11)
  {R_START_M,            R_CCW_BEGIN_M,  R_CW_BEGIN_M, R_START},
  // R_CW_BEGIN_M
  {R_START_M,            R_START_M,      R_CW_BEGIN_M, R_START | DIR_CW},
  // R_CCW_BEGIN_M
  {R_START_M,            R_CCW_BEGIN_M,  R_START_M,    R_START | DIR_CCW},
};
#else
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6

const unsigned char ttable[7][4] = {
  // R_START
  {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},
  // R_CW_FINAL
  {R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW},
  // R_CW_BEGIN
  {R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},
  // R_CW_NEXT
  {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},
  // R_CCW_BEGIN
  {R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},
  // R_CCW_FINAL
  {R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW},
  // R_CCW_NEXT
  {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
};
#endif

const int numReadings = 20;

int readings[numReadings];      // the readings from the analog input
int index = 0;              // the index of the current reading
int total = 0;                  // the running total
int currentOutputLevel = 0;

void setup()
{
  Joystick.begin();
  rotary_init();
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop()
{
  CheckAllButtons();
  CheckAllEncoders();
}

void CheckAllButtons(void)
{
  if (buttbx.getKeys())
  {
    for (int i = 0; i < LIST_MAX; i++)
    {
      if ( buttbx.key[i].stateChanged )
      {
        switch (buttbx.key[i].kstate)
        {
          case PRESSED:
            Joystick.setButton(buttbx.key[i].kcode, 1);
            break;

          case RELEASED:
            Joystick.setButton(buttbx.key[i].kcode, 0);
            break;

          case IDLE:
          case HOLD:
          default:
            break;
        }
      }
    }
  }
}
void rotary_init() {
  for (int i = 0; i < NUMROTARIES; i++) {
    pinMode(rotaries[i].pin1, INPUT);
    pinMode(rotaries[i].pin2, INPUT);
#ifdef ENABLE_PULLUPS
    digitalWrite(rotaries[i].pin1, HIGH);
    digitalWrite(rotaries[i].pin2, HIGH);
#endif
  }
}

unsigned char rotary_process(int _i) {
  //Serial.print("Processing rotary: ");
  //Serial.println(_i);
  unsigned char pinstate = (digitalRead(rotaries[_i].pin2) << 1) | digitalRead(rotaries[_i].pin1);
  rotaries[_i].state = ttable[rotaries[_i].state & 0xf][pinstate];
  return (rotaries[_i].state & 0x30);
}

void CheckAllEncoders(void) {
  for (int i = 0; i < NUMROTARIES; i++) {
    unsigned char result = rotary_process(i);
    if (result == DIR_CCW) {
      Serial.print("Rotary ");
      Serial.print(i);
      Serial.println(" <<< Going CCW");
      Joystick.setButton(rotaries[i].ccwchar, 1); delay(50); Joystick.setButton(rotaries[i].ccwchar, 0);
    };
    if (result == DIR_CW) {
      Serial.print("Rotary ");
      Serial.print(i);
      Serial.println(" >>> Going CW");
      Joystick.setButton(rotaries[i].cwchar, 1); delay(50); Joystick.setButton(rotaries[i].cwchar, 0);
    };
  }

}
