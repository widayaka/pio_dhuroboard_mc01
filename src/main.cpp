#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSerifItalic18pt7b.h>

#include "mc01_button.h"
#include "mc01_motor.h"
#include "mc01_encoder.h"
#include "mc01_display.h"

int servoChannel1 = 3;
int servoFrequency = 50;
int servoResolution = 16;
int pwmPeriod = 20000;

int servo1_pin = 32;

void servoWrite(int angle) {
  angle = constrain(angle, 0, 180);

  // Konversi sudut ke lebar pulsa 500-2400 us
  int pulseWidth = map(angle, 0, 270, 500, 3000);

  // Resolusi 16-bit: duty maksimum = 65535
  uint32_t duty = (uint32_t)pulseWidth * 65535UL
                  / pwmPeriod;

  ledcWrite(servoChannel1, duty);
}

void setup() {
  Serial.begin(115200);

  mc01_oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  mc01_oled.clearDisplay();

  ledcSetup(servoChannel1, servoFrequency, servoResolution);
  ledcAttachPin(servo1_pin, servoChannel1);

  init_mc01_button();
  init_mc01_motor();
  init_mc01_encoder();
}

void loop(){
  main_menu_program();
  delay(1000);
  main_menu_configure();
  delay(1000);
  main_menu_check();
  delay(1000);
}

