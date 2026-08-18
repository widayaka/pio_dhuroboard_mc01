#include <Arduino.h>
#include "gpio.h"
#include "motor.h"
#include "encoder.h"

void setup() {
  Serial.begin(115200);

  setup_gpio();
  setup_motor();
  setup_encoder();
}

void loop() {
  driveMotor1(50);
  driveMotor2(-50);
}