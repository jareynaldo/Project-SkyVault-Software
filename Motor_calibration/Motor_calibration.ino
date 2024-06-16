#include <Servo.h>

Servo ESC;

void setup() {
  ESC.attach(9);
  ESC.writeMicroseconds(2000); // Maximum throttle
  delay(2000); // Wait for 2 seconds
  ESC.writeMicroseconds(1000); // Minimum throttle
  delay(2000); // Wait for 2 seconds
}

void loop() {
  // Do nothing in the loop
}
