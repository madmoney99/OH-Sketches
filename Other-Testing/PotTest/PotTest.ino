// Program used to test the USB Joystick library when used as 
// a Flight Controller on the Arduino Leonardo or Arduino 
// Micro.
//
// Matthew Heironimus
// 2016-05-29 - Original Version
//------------------------------------------------------------

#include "Joystick.h"
#define NUMBUTTONS 10
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_MULTI_AXIS, NUMBUTTONS, 0,
  true, true, true, false, false, false,
  true, true, false, false, false);

const unsigned long gcCycleDelta = 1000;
const unsigned long gcAnalogDelta = 25;
const unsigned long gcButtonDelta = 500;
unsigned long gNextTime = 0;
unsigned int gCurrentStep = 0;


void testXYAxis(unsigned int currentStep)
{
  int xAxis;
  int yAxis;
  
  if (currentStep < 256)
  {
    xAxis = currentStep - 127;
    yAxis = -127;
    Joystick.setXAxis(xAxis);
    Joystick.setYAxis(yAxis);
  } 
  else if (currentStep < 512)
  {
    yAxis = currentStep - 256 - 127;
    Joystick.setYAxis(yAxis);
  }
  else if (currentStep < 768)
  {
    xAxis = 128 - (currentStep - 512);
    Joystick.setXAxis(xAxis);
  }
  else if (currentStep < 1024)
  {
    yAxis = 128 - (currentStep - 768);
    Joystick.setYAxis(yAxis);
  }
  else if (currentStep < 1024 + 128)
  {
    xAxis = currentStep - 1024 - 127;
    Joystick.setXAxis(xAxis);
    Joystick.setYAxis(xAxis);
  }
}

void testThrottleRudder(unsigned int value)
{
  Joystick.setThrottle(value);
  Joystick.setRudder(255 - value);
}

void setup() {

  Joystick.setXAxisRange(-127, 127);
  Joystick.setYAxisRange(-127, 127);
  Joystick.setZAxisRange(-127, 127);
  Joystick.setThrottleRange(0, 255);
  Joystick.setRudderRange(0, 255);
  
  
  pinMode(A0, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {


  // Turn indicator light on.
  digitalWrite(LED_BUILTIN, 1);
  
  if (millis() >= gNextTime)
  {
   
    if (gCurrentStep < 33)
    {
      gNextTime = millis() + gcButtonDelta;
      testSingleButtonPush(gCurrentStep);
    } 
    else if (gCurrentStep < 37)
    {
      gNextTime = millis() + gcButtonDelta;
      testMultiButtonPush(gCurrentStep - 33);
    }
    else if (gCurrentStep < (37 + 256))
    {
      gNextTime = millis() + gcAnalogDelta;
      testThrottleRudder(gCurrentStep - 37);
    }
    else if (gCurrentStep < (37 + 256 + 1024 + 128))
    {
      gNextTime = millis() + gcAnalogDelta;
      testXYAxis(gCurrentStep - (37 + 256));
    }
    
   
    gCurrentStep++;
    if (gCurrentStep >= (37 + 256 + 1024 + 128))
    {
      gNextTime = millis() + gcCycleDelta;
      gCurrentStep = 0;
    }
  }
}

