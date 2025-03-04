#include <Arduino.h>
#include <AFMotor.h> 

AF_DCMotor motorFrontLeft(1);
AF_DCMotor motorFrontRight(2);
AF_DCMotor motorBackLeft(3);
AF_DCMotor motorBackRight(4);

int initial_speed = 200;
long lastCommandTime = 0; // Stores the last time a valid command was received
bool moving = false; // Tracks if the car is currently moving

void setup() {
  Serial.begin(9600);
  while (!Serial);
  stopCar();
  updateSpeed(initial_speed);
}

void loop() {
  if (Serial.available()) {
    String message = Serial.readStringUntil('\n');
    message.trim(); // Remove any leading or trailing whitespace/newlines
    Serial.println("Received: " + message);

    if (message == "F") {
      moveForward();
      moving = true;
    } else if (message == "S") {
      stopCar();
      moving = false;
    } else if (message == "B") {
      moveBackward();
      moving = true;
    } else if (message == "L") {
      moveLeft();
      moving = true;
    } else if (message == "R") {
      moveRight();
      moving = true;
    } else if (message == "FL") {
      moveFrontLeft();
      moving = true;
    } else if (message == "FR") {
      moveFrontRight();
      moving = true;
    } else if (message == "BL") {
      moveBackLeft();
      moving = true;
    } else if (message == "BR") {
      moveBackRight();
      moving = true;
    } else if (message == "TL") {
      turnLeft();
      moving = true;
    } else if (message == "TR") {
      turnRight();
      moving = true;
    } else if (message == "RL") {
      roundLeft();
      moving = true;
    } else if (message == "RR") {
      roundRight();
      moving = true;
    } else if (message.startsWith("Update_")) { 
      int speed = message.substring(7).toInt();
      updateSpeed(speed);
      Serial.println("Speed Updated: " + String(speed));
      return; // Avoid resetting lastCommandTime, since speed update is not a movement command
    }

    lastCommandTime = millis(); // Update the last command received time
  }

  // Stop the car if no command is received for more than 200ms
  if (moving && (millis() - lastCommandTime > 200)) {
    stopCar();
    moving = false;
  }
}

// Movement functions
void moveForward() {
  motorFrontLeft.run(FORWARD);
  motorFrontRight.run(FORWARD);
  motorBackLeft.run(FORWARD);
  motorBackRight.run(FORWARD);
  Serial.println("Moving Forward");
}

void moveBackward() {
  motorFrontLeft.run(BACKWARD);
  motorFrontRight.run(BACKWARD);
  motorBackLeft.run(BACKWARD);
  motorBackRight.run(BACKWARD);
  Serial.println("Moving Backward");
}

void moveLeft() {
  motorFrontLeft.run(BACKWARD);
  motorFrontRight.run(FORWARD);
  motorBackLeft.run(FORWARD);
  motorBackRight.run(BACKWARD);
  Serial.println("Moving Left");
}

void moveRight() {
  motorFrontLeft.run(FORWARD);
  motorFrontRight.run(BACKWARD);
  motorBackLeft.run(BACKWARD);
  motorBackRight.run(FORWARD);
  Serial.println("Moving Right");
}

void moveFrontLeft() {
  motorFrontLeft.run(RELEASE);
  motorFrontRight.run(FORWARD);
  motorBackLeft.run(FORWARD);
  motorBackRight.run(RELEASE);
  Serial.println("Moving Forward Left");
}

void moveFrontRight() {
  motorFrontLeft.run(FORWARD);
  motorFrontRight.run(RELEASE);
  motorBackLeft.run(RELEASE);
  motorBackRight.run(FORWARD);
  Serial.println("Moving Forward Right");
}

void moveBackLeft() {
  motorFrontLeft.run(BACKWARD);
  motorFrontRight.run(RELEASE);
  motorBackLeft.run(RELEASE);
  motorBackRight.run(BACKWARD);
  Serial.println("Moving Back Left");
}

void moveBackRight() {
  motorFrontLeft.run(RELEASE);
  motorFrontRight.run(BACKWARD);
  motorBackLeft.run(BACKWARD);
  motorBackRight.run(RELEASE);
  Serial.println("Moving Back Right");
}

void turnLeft() {
  motorFrontLeft.run(BACKWARD);
  motorFrontRight.run(BACKWARD);
  motorBackLeft.run(FORWARD);
  motorBackRight.run(FORWARD);
  Serial.println("Turning Left");
}

void turnRight() {
  motorFrontLeft.run(FORWARD);
  motorFrontRight.run(FORWARD);
  motorBackLeft.run(BACKWARD);
  motorBackRight.run(BACKWARD);
  Serial.println("Turning Right");
}

void roundLeft() {
  motorFrontLeft.run(BACKWARD);
  motorFrontRight.run(FORWARD);
  motorBackLeft.run(RELEASE);
  motorBackRight.run(RELEASE);
  Serial.println("Rounding Left");
}

void roundRight() {
  motorFrontLeft.run(FORWARD);
  motorFrontRight.run(BACKWARD);
  motorBackLeft.run(RELEASE);
  motorBackRight.run(RELEASE);
  Serial.println("Rounding Right");
}

void stopCar() {
  motorFrontLeft.run(RELEASE);
  motorFrontRight.run(RELEASE);
  motorBackLeft.run(RELEASE);
  motorBackRight.run(RELEASE);
  Serial.println("Stopping");
}

void updateSpeed(int Speed) {
  motorFrontLeft.setSpeed(Speed);
  motorFrontRight.setSpeed(Speed);
  motorBackLeft.setSpeed(Speed);
  motorBackRight.setSpeed(Speed);
  Serial.println("Speed Updated: " + String(Speed));
}
