#include <Servo.h>

Servo baseServo;
Servo armServo;
Servo depthServo;
Servo gripServo;

String data = "";

void setup() {
  Serial.begin(9600);

  baseServo.attach(9);
  armServo.attach(10);
  depthServo.attach(11);
  gripServo.attach(6);
}

void loop() {
  if (Serial.available()) {
    data = Serial.readStringUntil('\n');

    int first = data.indexOf(',');
    int second = data.indexOf(',', first + 1);
    int third = data.indexOf(',', second + 1);

    int x = data.substring(0, first).toInt();
    int y = data.substring(first + 1, second).toInt();
    float z = data.substring(second + 1, third).toFloat();
    int grip = data.substring(third + 1).toInt();

    int baseAngle = map(x, 0, 640, 0, 180);
    int armAngle  = map(y, 0, 480, 0, 180);
    int depthAngle = map(z * 100, -50, 50, 0, 180);

    baseServo.write(baseAngle);
    armServo.write(armAngle);
    depthServo.write(depthAngle);

    if (grip == 1) {
      gripServo.write(30);   // close
    } else {
      gripServo.write(90);   // open
    }
  }
}