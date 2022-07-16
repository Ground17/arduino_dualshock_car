#include <PS4BT.h>
/// #include <PS4USB.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statement in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

const int IN1 = 2;       //control pin for first motor
const int IN2 = 3;       //control pin for first motor
const int IN3 = 4;       //control pin for second motor
const int IN4 = 5;       //control pin for second motor

// PIN9 == INT, PIN10 == SS, PIN11 == MOSI, PIN12 == MISO, PIN13 == SCK
USB Usb;
/// PS4USB PS4(&Usb);
//USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

/* You can create the instance of the PS4BT class in two ways */
// This will start an inquiry and then pair with the PS4 controller - you only have to do this once
// You will need to hold down the PS and Share button at the same time, the PS4 controller will then start to blink rapidly indicating that it is in pairing mode
PS4BT PS4(&Btd, PAIR);

// After that you can simply create the instance like so and then press the PS button on the device
//PS4BT PS4(&Btd);

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);  
  pinMode(IN4, OUTPUT);
  
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
/* check the signal */
//    Serial.print(F("\r\nLeftHatX: "));
//    Serial.print(PS4.getAnalogHat(LeftHatX));
//    Serial.print(F("\tLeftHatY: "));
//    Serial.print(PS4.getAnalogHat(LeftHatY));
//    Serial.print(F("\tRightHatX: "));
//    Serial.print(PS4.getAnalogHat(RightHatX));
//    Serial.print(F("\tRightHatY: "));
//    Serial.print(PS4.getAnalogHat(RightHatY));
//    Serial.print("\n");

/* It was written to simplify the code, but for some reason, there are a lot of errors */
//    int rightYValue = PS4.getAnalogHat(RightHatY);
//    int leftXValue = PS4.getAnalogHat(LeftHatX);

//    activeMotor(
//      rightYValue < 20, 
//      rightYValue > 236, 
//      leftXValue < 20, 
//      leftXValue > 236
//    );

    if (20 <= PS4.getAnalogHat(RightHatY) && PS4.getAnalogHat(RightHatY) <= 236 
      && 20 <= PS4.getAnalogHat(LeftHatX) && PS4.getAnalogHat(LeftHatX) <= 236 ) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      return;
    }
    
    if (PS4.getAnalogHat(RightHatY) < 20) { // up
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    } else if (PS4.getAnalogHat(RightHatY) > 236) { // down
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    } else {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
      Serial.print("\nrotate the right joystick to move forward/backward");
    }
    
    if (PS4.getAnalogHat(LeftHatX) < 20) { // left
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    } else if (PS4.getAnalogHat(LeftHatX) > 236) { // right
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    } else {
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);
      Serial.print("\nrotate the joystick to move left/right");
    }
  } else {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
  }
}

//void activeMotor(bool isIn1, bool isIn2, bool isIn3, bool isIn4) {
//  digitalWrite(IN1, isIn1 ? HIGH : LOW);
//  digitalWrite(IN2, isIn2 ? HIGH : LOW);
//  digitalWrite(IN3, isIn3 ? HIGH : LOW);
//  digitalWrite(IN4, isIn4 ? HIGH : LOW);
//  
//  Serial.print(isIn1 ? HIGH : LOW);
//  Serial.print(" ");
//  Serial.print(isIn2 ? HIGH : LOW);
//  Serial.print(" ");
//  Serial.print(isIn3 ? HIGH : LOW);
//  Serial.print(" ");
//  Serial.print(isIn4 ? HIGH : LOW);
//  Serial.print("\n");
//}