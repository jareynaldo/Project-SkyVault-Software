#include <Servo.h>

Servo ESC;
int Speed;
int counter;

// Define pin numbers
const int greenLEDPin = 4;
const int yellowLEDPin = 5;
const int redLEDPin = 6;
const int buzzerPin = 11;

// Enumeration to define states
enum State {UNARMED, ARMED, DOING};
State currentState = UNARMED;

void setup() {
  // Attach the ESC to pin 9
  ESC.attach(9);
  armESC();

  // Set pins as outputs
  pinMode(greenLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  
  setUnarmed(); //state
}

void loop() {
  delay(5000);
  setArmed();
  delay(5000);
  // run program
  setDoing();
  delay(5000);
  setUnarmed();
  delay(5000);

}

void armESC() {
  ESC.writeMicroseconds(1000); // Minimum throttle
  delay(2000); // Wait for 2 seconds to arm the ESC
}

void setUnarmed() {
  ESC.write(0);
  currentState = UNARMED;
  digitalWrite(greenLEDPin, HIGH);
  digitalWrite(yellowLEDPin, LOW);
  digitalWrite(redLEDPin, LOW);
  
  tone(buzzerPin, 500); // Send 500Hz sound signal...
  delay(1000);        
  noTone(buzzerPin);
}

void setArmed() {
  currentState = ARMED;
  digitalWrite(greenLEDPin, LOW);
  digitalWrite(yellowLEDPin, HIGH);
  digitalWrite(redLEDPin, LOW);

  tone(buzzerPin, 5000); // Send 1KHz sound signal...
  delay(1000);        
  noTone(buzzerPin);
}

void setDoing() {
  currentState = DOING;
  digitalWrite(greenLEDPin, LOW);
  digitalWrite(yellowLEDPin, LOW);
  digitalWrite(redLEDPin, HIGH);
  tone(buzzerPin, 500); // Send 1KHz sound signal...
  delay(1000);        
  noTone(buzzerPin);
  
  upsideDownsie(); // Call the function to perform the desired speed pattern

}

void upsideDownsie() {
  // Upward pattern
  for (counter = 0; counter < 180; counter++) {
    Speed = counter;
    ESC.write(Speed);
    delay(100); // Adjust the delay for smooth transition
  }
  
  for (counter = 180; counter > 150; counter--) {
    Speed = counter;
    ESC.write(Speed);
    delay(100);
  }
  
  for (counter = 150; counter < 200; counter++) {
    Speed = counter;
    ESC.write(Speed);
    delay(100); 
  }
  
  // Downward pattern
  for (counter = 200; counter >= 150; counter--) {
    Speed = counter;
    ESC.write(Speed);
    delay(100); 
  }
  
  for (counter = 150; counter >= 0; counter--) {
    Speed = counter;
    ESC.write(Speed);
    delay(100); 
  }
}

void smoothLanding() {
  // Start from a high speed and gradually slow down
  Speed = 200; // Starting speed, adjust as needed
  int decrement = 5; // Speed decrement, adjust for finer control
  
  while (Speed > 0) {
    ESC.write(Speed);
    delay(100); // Adjust the delay for a smooth transition
    if (Speed > 100) {
      decrement = 5; // Fast decrement initially
    } else if (Speed > 50) {
      decrement = 2; // Slow down decrement as it approaches lower speed
    } else {
      decrement = 1; // Very fine decrement near stop
    }
    Speed -= decrement;
  }
  ESC.write(0); // Ensure motor is stopped
}

void pulseWave() {
  // PulseWave pattern: Speed up, slow down, speed up again
  // Speed up to maximum
  for (counter = 0; counter <= 200; counter++) {
    Speed = counter;
    ESC.write(Speed);
    delay(50); // Adjust the delay for smooth transition
  }
  
  // Slow down to half speed
  for (counter = 200; counter >= 100; counter--) {
    Speed = counter;
    ESC.write(Speed);
    delay(50);
  }
  
  // Speed up again to maximum
  for (counter = 100; counter <= 200; counter++) {
    Speed = counter;
    ESC.write(Speed);
    delay(50);
  }
  
  // Slow down to zero
  for (counter = 200; counter >= 0; counter--) {
    Speed = counter;
    ESC.write(Speed);
    delay(50);
  }
}
void waveRider() {
  // WaveRider pattern: Oscillate speed in a wave-like manner
  int amplitude = 100; // Amplitude of the wave
  int offset = 100;    // Offset to ensure the speed stays positive
  int period = 200;    // Number of steps in one period of the wave

  for (int i = 0; i < period; i++) {
    Speed = offset + amplitude * sin(2 * PI * i / period);
    ESC.write(Speed);
    delay(50); // Adjust the delay for smooth transition
  }
}

void testOne() {
  // Throttle up to halfway (using the range 1000 to 2000 microseconds)
  for (Speed = 1000; Speed <= 1500; Speed += 10) { // Halfway point in microseconds
    ESC.writeMicroseconds(Speed);
    delay(100); // Adjust the delay for smooth transition
  }

    // Throttle back down to zero
  for (Speed = 1500; Speed >= 1000; Speed -= 10) {
    ESC.writeMicroseconds(Speed);
    delay(100); // Adjust the delay for smooth transition
  }
 }

void maxSpeedTest() {
  // Ramp up from 0 to max in 5 seconds
  int maxSpeed = 2000; // Maximum speed in microseconds
  int minSpeed = 1000; // Minimum speed in microseconds
  int stepDelay = 5;   // Step delay in milliseconds
  int steps = (maxSpeed - minSpeed) / (5000 / stepDelay); // Calculate the number of steps
  
  for (Speed = minSpeed; Speed <= maxSpeed; Speed += steps) {
    ESC.writeMicroseconds(Speed);
    delay(stepDelay);
  }

  // Hold at max speed for 3 seconds
  ESC.writeMicroseconds(maxSpeed);
  delay(3000);

  // Drop back down to 0 in 2 seconds
  steps = (maxSpeed - minSpeed) / (2000 / stepDelay); // Calculate the number of steps for 2 seconds
  
  for (int Speed = maxSpeed; Speed >= minSpeed; Speed -= steps) {
    ESC.writeMicroseconds(Speed);
    delay(stepDelay);
  }
}
