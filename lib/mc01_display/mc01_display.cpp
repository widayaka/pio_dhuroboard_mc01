#include <Arduino.h>
#include "mc01_display.h"
#include "mc01_button.h"
#include <Adafruit_GFX.h>
#include <Fonts/FreeSerifItalic18pt7b.h>

int menu = 0;
int pilih_menu = 0 ;

char robot_name[] = "DHURO BOARD MC01";

#define MAIN_MENU_COUNT 4
const char* main_menu[] = {"Robot", "Check", "GPIOs", "PIDs"};

#define MODE_ROBOT_COUNT 8
const char* mode_robot[] = {"DhuROS DDMR", "DhuROS Omnibot", "Socc. Std", "Socc. Omni", "Socc. Meca", "Trans. Std", "Trans. Omni", "Trans. Meca"};

#define CHECK_ROBOT_COUNT 3
const char* check_robot[] = {" Motor ", "  IMU  ", "Encoder"};

#define SERVO_SET_COUNT 2
const char* servo_set[] = {"Pin", "Set"};

#define SERVO_PIN_COUNT 6
const char* servo_pin[] = {"IO32", "IO33", "IO25", "IO26", "IO27", "IO14"};

#define PID_SET_COUNT 2
const char* pid_set[] = {"Encoder", "IMU"};

int index_page = 0;
int index_mode = 0;
int index_check = 0;
int pilih_set_servo = 0;

Adafruit_SSD1306 mc01_oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void templateMainMenu(){
    mc01_oled.setTextSize(1);
    mc01_oled.setTextColor(SSD1306_WHITE);

    mc01_oled.drawRoundRect(0, 0, mc01_oled.width(), 11, 3, SSD1306_WHITE);
    mc01_oled.setCursor(mc01_oled.width()/2 - 47, 2);  mc01_oled.println(robot_name);

    // 1x4 left menu bar
    for (int y=1;y<5;y++){
        mc01_oled.setTextSize(1); 
        mc01_oled.setTextColor(SSD1306_BLACK);
        mc01_oled.drawRoundRect(0, y*13, 35, 11, 3, SSD1306_WHITE);
    }

    // 1x2 right menu bar
    for (int y=1;y<3;y++){
        mc01_oled.setTextSize(1); 
        mc01_oled.setTextColor(SSD1306_BLACK);
        mc01_oled.drawRoundRect(37, y*13, mc01_oled.width() - 37, 11, 3, SSD1306_WHITE);
    }

    // 1x2 center menu bar
    for (int y=3;y<5;y++){
        mc01_oled.setTextSize(1); 
        mc01_oled.setTextColor(SSD1306_BLACK);
        mc01_oled.drawRoundRect(37, y*13, 44, 11, 3, SSD1306_WHITE);
    }
    
    // 1x2 right menu bar
    for (int y=3;y<5;y++){
        mc01_oled.setTextSize(1); 
        mc01_oled.setTextColor(SSD1306_BLACK);
        mc01_oled.drawRoundRect(83, y*13, 44, 11, 3, SSD1306_WHITE);
    }

    mc01_oled.display();
}

void drawMainMenu(int selected){
    templateMainMenu();
    for (int i=0;i<MAIN_MENU_COUNT;i++){
        int y = 13 + (i * 13);
        if (i == selected){
            mc01_oled.setTextColor(SSD1306_BLACK);
            mc01_oled.fillRoundRect(0, y, 35, 11, 3, SSD1306_WHITE);
        }
        else{
            mc01_oled.setTextColor(SSD1306_WHITE);
            mc01_oled.fillRoundRect(0, y, 35, 11, 3, SSD1306_BLACK);
            mc01_oled.drawRoundRect(0, y, 35, 11, 3, SSD1306_WHITE);
        }
        mc01_oled.setCursor(3, y + 2);
        mc01_oled.println(main_menu[i]);
    }
    mc01_oled.display();
}

void mainMenu(){
    drawMainMenu(pilih_menu);
    if (read_button_dn()){delay(100); pilih_menu++; if (pilih_menu > MAIN_MENU_COUNT - 1){pilih_menu = 0;}}
    if (read_button_up()){delay(100); pilih_menu--; if (pilih_menu < 0){pilih_menu = MAIN_MENU_COUNT - 1;}}
    if (read_button_ok()){delay(100); menu = pilih_menu + 1; mc01_oled.clearDisplay();}
}

void main_menu_configure(void){
    mc01_oled.clearDisplay();
  
  // rect1
  mc01_oled.drawRoundRect(1, 1, 126, 13, 3, 1); 
  
  // DHURO STRIKE-X V2.0
  mc01_oled.setTextColor(1);
  mc01_oled.setTextWrap(false);
  mc01_oled.setFont(NULL);
  mc01_oled.setCursor(8, 4);
  mc01_oled.print("DHURO STRIKE-X V2.0");

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