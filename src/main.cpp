#include <Arduino.h>
#include "ESP32Servo.h"

#include "mc02_button.h"
#include "mc02_motor.h"
#include "mc02_encoder.h"
#include "mc02_display.h"

void setup() {
  Serial.begin(115200);
  mc02_oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  mc02_oled.clearDisplay();

  setup_button();
  setup_motor();
  setup_encoder();
}

void loop(){

}