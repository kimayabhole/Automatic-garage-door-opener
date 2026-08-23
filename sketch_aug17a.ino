#include <ESP32Servo.h>

int servoPin = 14;
int trigPin = 5;
int echoPin = 18;
int doorClosed = 90;
int doorOpen = 0;

Servo myServo;
float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return 999.0; // Out of range or no echo
  return (duration * 0.0343) / 2;
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  ESP32PWM::allocateTimer(0);
  myServo.setPeriodHertz(50);
  myServo.attach(servoPin, 500, 2400);

  // default state for door is closed
  myServo.write(doorClosed);
}

void loop() {
  float distance = getDistance();

  //object within 10 cm -> Open gate
  if (distance > 0 && distance <= 10) {
    myServo.write(doorOpen);
    delay(500); // Give the servo time to fully swing open

    //wait and hold the door open while the object is passing through
    while (getDistance() <= 10) {
      delay(50);
    }

    // object passes and clears the sensor -> gate is closed
    delay(500);  
    myServo.write(doorClosed);
  }

  delay(100);
}