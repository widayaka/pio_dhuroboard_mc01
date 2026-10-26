#include <Arduino.h>
#include "mc02_display.h"
#include "button.h"

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

Adafruit_SSD1306 mc02_oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void templateMainMenu(){
    mc02_oled.setTextSize(1);
    mc02_oled.setTextColor(SSD1306_WHITE);

    mc02_oled.drawRoundRect(0, 0, mc02_oled.width(), 11, 3, SSD1306_WHITE);
    mc02_oled.setCursor(mc02_oled.width()/2 - 47, 2);  mc02_oled.println(robot_name);

    // 1x4 left menu bar
    for (int y=1;y<5;y++){
        mc02_oled.setTextSize(1); 
        mc02_oled.setTextColor(SSD1306_BLACK);
        mc02_oled.drawRoundRect(0, y*13, 35, 11, 3, SSD1306_WHITE);
    }

    // 1x2 right menu bar
    for (int y=1;y<3;y++){
        mc02_oled.setTextSize(1); 
        mc02_oled.setTextColor(SSD1306_BLACK);
        mc02_oled.drawRoundRect(37, y*13, mc02_oled.width() - 37, 11, 3, SSD1306_WHITE);
    }

    // 1x2 center menu bar
    for (int y=3;y<5;y++){
        mc02_oled.setTextSize(1); 
        mc02_oled.setTextColor(SSD1306_BLACK);
        mc02_oled.drawRoundRect(37, y*13, 44, 11, 3, SSD1306_WHITE);
    }
    
    // 1x2 right menu bar
    for (int y=3;y<5;y++){
        mc02_oled.setTextSize(1); 
        mc02_oled.setTextColor(SSD1306_BLACK);
        mc02_oled.drawRoundRect(83, y*13, 44, 11, 3, SSD1306_WHITE);
    }

    mc02_oled.display();
}

void drawMainMenu(int selected){
    templateMainMenu();
    for (int i=0;i<MAIN_MENU_COUNT;i++){
        int y = 13 + (i * 13);
        if (i == selected){
            mc02_oled.setTextColor(SSD1306_BLACK);
            mc02_oled.fillRoundRect(0, y, 35, 11, 3, SSD1306_WHITE);
        }
        else{
            mc02_oled.setTextColor(SSD1306_WHITE);
            mc02_oled.fillRoundRect(0, y, 35, 11, 3, SSD1306_BLACK);
            mc02_oled.drawRoundRect(0, y, 35, 11, 3, SSD1306_WHITE);
        }
        mc02_oled.setCursor(3, y + 2);
        mc02_oled.println(main_menu[i]);
    }
    mc02_oled.display();
}

void mainMenu(){
    drawMainMenu(pilih_menu);
    if (read_button_dn()){delay(100); pilih_menu++; if (pilih_menu > MAIN_MENU_COUNT - 1){pilih_menu = 0;}}
    if (read_button_up()){delay(100); pilih_menu--; if (pilih_menu < 0){pilih_menu = MAIN_MENU_COUNT - 1;}}
    if (read_button_ok()){delay(100); menu = pilih_menu + 1; mc02_oled.clearDisplay();}
}