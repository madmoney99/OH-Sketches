#include <Wire.h>
#include <TCA9555.h>
#include <Joystick.h>

// Define the TCA9555 objects for each row
TCA9555 ddiButtons[4] = {
  TCA9555(0x23), // Left Row
  TCA9555(0x20), // Top Row
  TCA9555(0x22), // Right Row
  TCA9555(0x21)  // Bottom Row
};

const int buttonCountPerRow = 5;
const int totalButtons = 4 * buttonCountPerRow;

// Joystick object
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_GAMEPAD,
                   27, 0, // Button Count (+3 for switch), Hat Switch Count
                   false, false, false, // X, Y, Z axes
                   false, false, false, // Rx, Ry, Rz axes
                   false, false,       // Rudder, Throttle axes
                   false, false, false); // Accelerator, Brake, Steering

// Define pin constants
const int SWITCH_PIN_1 = A2;
const int SWITCH_PIN_2 = A1;
const int SWITCH_PIN_3 = A0;

// Encoder pins used as push buttons
const int ENCODER_BTN1_PIN = 8;  // Encoder 1 CLK pin as a push button
const int ENCODER_BTN2_PIN = 10; // Encoder 1 DT pin as a push button
const int ENCODER_BTN3_PIN = 4;   // Encoder 2 CLK pin as a push button
const int ENCODER_BTN4_PIN = 7;   // Encoder 2 DT pin as a push button

// Pin connected to MOSFET gate for LED control
const int LED_MOSFET_PIN = 9;

void setup() {
  // Initialize Serial communication for debugging (optional)
  Serial.begin(9600);

  // Initialize I2C communication
  Wire.begin();
  delay(100);

  // Initialize each TCA9555 and set pins as inputs
  for (int i = 0; i < 4; i++) {
    if (!ddiButtons[i].begin()) {
      Serial.print("Failed to initialize TCA9555 at address 0x");
      Serial.println(ddiButtons[i].getAddress(), HEX);
      while (1); // Halt if initialization fails
    }
    for (int j = 0; j < buttonCountPerRow; j++) {
      ddiButtons[i].pinMode1(j, INPUT); // Set pin mode as INPUT
      ddiButtons[i].write1(j, HIGH); // Enable internal pull-up resistor
    }
  }

  // Set pin modes for switches
  pinMode(SWITCH_PIN_1, INPUT_PULLUP);
  pinMode(SWITCH_PIN_2, INPUT_PULLUP);
  pinMode(SWITCH_PIN_3, INPUT_PULLUP);

  // Set pin modes for encoder push buttons
  pinMode(ENCODER_BTN1_PIN, INPUT_PULLUP);
  pinMode(ENCODER_BTN2_PIN, INPUT_PULLUP);
  pinMode(ENCODER_BTN3_PIN, INPUT_PULLUP);
  pinMode(ENCODER_BTN4_PIN, INPUT_PULLUP);

  // Set pin mode for MOSFET control
  pinMode(LED_MOSFET_PIN, OUTPUT);

  // Start with 0% duty cycle (LEDs off)
  analogWrite(LED_MOSFET_PIN, 0);

  // Initialize Joystick Library
  Joystick.begin();
}

void loop() {
  // Read and send button states from TCA9555 buttons
  int buttonIndex = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < buttonCountPerRow; j++) {
      int buttonState = ddiButtons[i].read1(j); // Read digital state
      bool pressed = (buttonState == HIGH); // Assuming LOW means pressed
      Joystick.setButton(buttonIndex, pressed);
      buttonIndex++;
    }
  }

  // Read the state of switches
  int switchState1 = digitalRead(SWITCH_PIN_1);
  int switchState2 = digitalRead(SWITCH_PIN_2);
  int switchState3 = digitalRead(SWITCH_PIN_3);

  // Update Joystick button states for switches
  Joystick.setButton(20, !switchState1); // Invert because pull-up
  Joystick.setButton(21, !switchState2); // Invert because pull-up
  Joystick.setButton(22, !switchState3); // Invert because pull-up

  // Read encoder push button states
  int encoderBtn1State = digitalRead(ENCODER_BTN1_PIN);
  int encoderBtn2State = digitalRead(ENCODER_BTN2_PIN);
  int encoderBtn3State = digitalRead(ENCODER_BTN3_PIN);
  int encoderBtn4State = digitalRead(ENCODER_BTN4_PIN);

  // Update Joystick button states for encoder buttons
  Joystick.setButton(23, !encoderBtn1State); // Encoder 1 CLK button
  Joystick.setButton(24, !encoderBtn2State); // Encoder 1 DT button
  Joystick.setButton(25, !encoderBtn3State); // Encoder 2 CLK button
  Joystick.setButton(26, !encoderBtn4State); // Encoder 2 DT button

  // Set PWM duty cycle to 25% for LEDs (assuming PWM range is 0-255)
  int pwmValue = 10; // 25% of 255
  analogWrite(LED_MOSFET_PIN, pwmValue);

  // Optional: Print PWM value to Serial for debugging
  Serial.print("LED PWM Value: ");
  Serial.println(pwmValue);

  // Delay a short time to avoid flooding the USB communication
  delay(50);
}
