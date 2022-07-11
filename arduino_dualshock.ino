#include <PS4BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statement in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
int IN1 = 3;       //control pin for first motor
int IN2 = 4;       //control pin for first motor
int IN3 = 5;        //control pin for second motor
int IN4 = 6;        //control pin for second motor

// PIN9 == INT, PIN10 ==SS, PIN11 == MOSI, PIN12 == MISO, PIN13 == SCK
USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

/* You can create the instance of the PS4BT class in two ways */
// This will start an inquiry and then pair with the PS4 controller - you only have to do this once
// You will need to hold down the PS and Share button at the same time, the PS4 controller will then start to blink rapidly indicating that it is in pairing mode
PS4BT PS4(&Btd, PAIR);

// After that you can simply create the instance like so and then press the PS button on the device
//PS4BT PS4(&Btd);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;

void setup() {
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);  
  pinMode(IN4, OUTPUT);
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif

  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));
}

void loop() {
  Usb.Task();

  if (PS4.connected()) {
    if (PS4.getButtonClick(TRIANGLE)) {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      Serial.print(F("\r\nTriangle"));
      // PS4.setRumbleOn(RumbleLow);
    } else if (PS4.getButtonClick(CROSS)) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      Serial.print(F("\r\nCross"));
      // PS4.setRumbleOn(RumbleLow);
    } else {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      Serial.print(F("\r\nclick 'O' or 'X'"));
    }
    
    if(PS4.getAnalogHat(LeftHatX) < 20) {
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      Serial.print("\nHatX: 50 ");
    } else if(PS4.getAnalogHat(LeftHatX) > 236) {
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      Serial.print("\nHatX: 200 ");
    } else {
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      Serial.print("\nrotate the joystick");
    }
  }
}
