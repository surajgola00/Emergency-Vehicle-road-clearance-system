#include <Arduino.h>
#include <IRremote.hpp> // IR remote library

// Define IR receiver pin
#define IR_RECEIVE_PIN 2

// Remote button codes (Replace with your actual codes)
#define F  0x2  // Example IR codes
#define B 0x8
#define L     0x4
#define R    0x6
#define FL    0x1
#define FR    0x3
#define BL    0x7
#define BR    0x9
#define TL    0x110
#define TR    0x111
#define RL    0x109
#define RR    0x112
#define S     0x5

#define SU     0x88
#define SD     0x89

void setup() {
  Serial.begin(9600);
  while (!Serial);  // Wait for Serial Monitor

  Serial.println("IR Remote-Controlled Mecanum Car Ready");

  // Start IR receiver
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

int Speed = 200;

void loop() {
    if (IrReceiver.decode()) {
      if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
          IrReceiver.resume();
          return;
      }
      
      uint8_t command = IrReceiver.decodedIRData.command;
      Serial.print("Received Command: 0x");
      Serial.println(command, HEX);

      switch (command) {
          case F:
              Serial.println("F");
              break;
          case B:
              Serial.println("B");
              break;
          case L:
              Serial.println("L");
              break;
          case R:
              Serial.println("R");
              break;
          case FL:
              Serial.println("FL");
              break;
          case FR:
              Serial.println("FR");
              break;
          case BL:
              Serial.println("BL");
              break;
          case BR:
              Serial.println("BR");
              break;
          case TL:
              Serial.println("TL");
              break;
          case TR:
              Serial.println("TR");
              break;
          case RL:
              Serial.println("RL"); // Fixed RL case output
              break;
          case RR:
              Serial.println("RR");
              break;
          case S:
              Serial.println("S");
              break;
          case SU:
              updatedSpeed(true);
              Serial.println("Update_" + String(Speed));
              break;
          case SD:
              updatedSpeed(false);
              Serial.println("Update_" + String(Speed));
              break;
          default:
              Serial.println("Unknown Command");
              break;
      }
      IrReceiver.resume(); // Prepare for next signal
    }
}

void updatedSpeed(bool inc) {
  if (inc) {
    Speed = Speed + 25;
    if (Speed >= 255){
      Speed = 255;
    }
  } else {
    Speed = Speed - 25;
    if (Speed <= 100) {
      Speed = 100;
    }
  }
}