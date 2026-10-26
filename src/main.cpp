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
  mc01_oled.clearDisplay();
  
  // rect1
  mc01_oled.drawRoundRect(1, 1, 126, 13, 3, 1); 
  
  // Dhuro Board MC-01
  mc01_oled.setTextColor(1);
  mc01_oled.setTextWrap(false);
  mc01_oled.setFont(NULL);
  mc01_oled.setCursor(14, 4);
  mc01_oled.print("DHURO BOARD MC-01");

  // rect2
  mc01_oled.fillRoundRect(1, 16, 59, 13, 3, 1);

  // Configuration
  mc01_oled.setFont(NULL);
  mc01_oled.setTextColor(0);
  mc01_oled.setCursor(4, 19);
  mc01_oled.print("Configure");

  // rect3
  mc01_oled.drawRoundRect(1, 31, 59, 13, 3, 1);

  // Check
  mc01_oled.setFont(NULL);
  mc01_oled.setTextColor(1);
  mc01_oled.setCursor(16, 34);
  mc01_oled.print("Check");

  // rect4
  mc01_oled.drawRoundRect(1, 46, 59, 13, 3, 1);

  // Program
  mc01_oled.setFont(NULL);
  mc01_oled.setTextColor(1);
  mc01_oled.setCursor(10, 49);
  mc01_oled.print("Program");

  // rect5
  mc01_oled.drawRoundRect(62, 16, 65, 43, 3, 1);
  
  // Go!
  mc01_oled.setTextColor(1);
  mc01_oled.setCursor(65, 42);
  mc01_oled.setFont(&FreeSerifItalic18pt7b);
  mc01_oled.print("GO!");
  mc01_oled.display();
}

