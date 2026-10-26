#include <Arduino.h>
#include "ESP32Servo.h"

#include "mc01_button.h"
#include "mc01_motor.h"
#include "mc01_encoder.h"
#include "mc01_display.h"

void setup() {
  Serial.begin(115200);

  mc01_oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  mc01_oled.clearDisplay();

  init_mc01_button();
  init_mc01_motor();
  init_mc01_encoder();
}

void loop(){
  
}