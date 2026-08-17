#include <Arduino.h>
#include "gpio.h"
#include "encoder.h"

void setup() {
  Serial.begin(115200);

  setup_gpio();
  setup_encoder();
}

void loop() {
  
}