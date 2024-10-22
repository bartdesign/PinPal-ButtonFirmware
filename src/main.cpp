#include <Joystick_ESP32S2.h>
#include <Bounce2.h>

// Pin definitions
#define LEFT_SHOULDER_BUTTON 4
#define RIGHT_SHOULDER_BUTTON 3
#define DPAD_LEFT 11
#define DPAD_RIGHT 10
#define BUTTON_B 6
#define DPAD_DOWN 5

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
                   10, 1,                 // Button Count, Hat Switch Count
                   true, true, true,    // X and Y, but no Z Axis
                   true, true, false,  // No Rx, Ry, or Rz
                   false, false,         // No rudder or throttle
                   false, false, false); // No accelerator, brake, or steering

// Create Bounce objects for debouncing
Bounce2::Button leftFlipperButton = Bounce2::Button();
Bounce2::Button rightFlipperButton = Bounce2::Button();
Bounce2::Button leftNudgeButton = Bounce2::Button();
Bounce2::Button rightNudgeButton = Bounce2::Button();
Bounce2::Button startGameButton = Bounce2::Button();
Bounce2::Button plungeButton = Bounce2::Button();

void setup()
{
  // Initialize pins for buttons with Bounce debouncers
  leftFlipperButton.attach(LEFT_SHOULDER_BUTTON, INPUT_PULLUP);
  leftFlipperButton.interval(5); // Debounce interval in milliseconds
  leftFlipperButton.setPressedState(LOW);

  rightFlipperButton.attach(RIGHT_SHOULDER_BUTTON, INPUT_PULLUP);
  rightFlipperButton.interval(5);
  rightFlipperButton.setPressedState(LOW);

  leftNudgeButton.attach(DPAD_LEFT, INPUT_PULLUP);
  leftNudgeButton.interval(5);
  leftNudgeButton.setPressedState(LOW);

  rightNudgeButton.attach(DPAD_RIGHT, INPUT_PULLUP);
  rightNudgeButton.interval(5);
  rightNudgeButton.setPressedState(LOW);

  startGameButton.attach(BUTTON_B, INPUT_PULLUP);
  startGameButton.interval(5);
  startGameButton.setPressedState(LOW);

  plungeButton.attach(DPAD_DOWN, INPUT_PULLUP);
  plungeButton.interval(5);
  plungeButton.setPressedState(LOW);

  USB.PID(0x02D1);
	USB.VID(0x045E);
	USB.productName("Xbox One Controller");
	USB.manufacturerName("Microsoft");
	USB.begin();

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);
  Joystick.setZAxisRange(-1, 1);
  Joystick.setRxAxisRange(-1, 1);
  Joystick.setRyAxisRange(-1, 1);
}

void loop()
{
  // Update all debouncers
  leftFlipperButton.update();
  rightFlipperButton.update();
  leftNudgeButton.update();
  rightNudgeButton.update();
  startGameButton.update();
  plungeButton.update();

  //// Left Flipper

  if (leftFlipperButton.pressed())
  {
    Joystick.setButton(4, 1);
  }
  if (leftFlipperButton.released())
  {
    Joystick.setButton(4, 0);
  }

  //// Right Flipper

  if (rightFlipperButton.pressed())
  {
    Joystick.setButton(5, 1);
  }
  if (rightFlipperButton.released())
  {
    Joystick.setButton(5, 0);
  }

  //// Left Nudge

  if (leftNudgeButton.pressed())
  {
    Joystick.setHatSwitch(0, 90);
  }
  if (leftNudgeButton.released())
  {
    Joystick.setHatSwitch(0, -1);
  }

  //// Right Nudge

  if (rightNudgeButton.pressed())
  {
    Joystick.setHatSwitch(0, 270);
  }
  if (rightNudgeButton.released())
  {
    Joystick.setHatSwitch(0, -1);
  }

  //// Start Game

  if (startGameButton.pressed())
  {
    Joystick.setButton(1, 1);
  }
  if (startGameButton.released())
  {
    Joystick.setButton(1, 0);
  }

  //// Plunger

  if (plungeButton.pressed())
  {
    Joystick.setHatSwitch(0, 180);
  }
  if (plungeButton.released())
  {
    Joystick.setHatSwitch(0, -1);
  }

  delay(10);
}
