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
int page_idx_main_menu = 0;
int page_idx_menu_program = 0;

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

// void mainMenu(){
//     drawMainMenu(pilih_menu);
//     if (read_button_dn()){delay(100); pilih_menu++; if (pilih_menu > MAIN_MENU_COUNT - 1){pilih_menu = 0;}}
//     if (read_button_up()){delay(100); pilih_menu--; if (pilih_menu < 0){pilih_menu = MAIN_MENU_COUNT - 1;}}
//     if (read_button_ok()){delay(100); menu = pilih_menu + 1; mc01_oled.clearmc01_oled();}
// }

void mainMenu(){
    switch (page_idx_main_menu){
        case 0: main_menu_program(); break;
        case 1: main_menu_configure();  break;
        case 2: main_menu_check();  break;
    }

    if (read_button_dn()){
        delay(50); 
        page_idx_main_menu++; 
        if (page_idx_main_menu > 2){
            page_idx_main_menu = 0;
        }
    }
    
    if (read_button_up()){
        delay(50); 
        page_idx_main_menu--; 
        if (page_idx_main_menu < 0){
            page_idx_main_menu = 2;}
        }

    if (read_button_ok()){
        delay(50); 
        index_page = page_idx_main_menu;
    }
}

void menuProgram(void){
    switch (page_idx_menu_program){
        case 0: program_socc_4wd(); break;
        case 1: program_socc_omni(); break;
        case 2: program_socc_meca(); break;
    }

    if (read_button_dn()){
        delay(100); 
        page_idx_menu_program++; 
        if (page_idx_menu_program > 2){
            page_idx_menu_program = 0;
        }
    }
    
    if (read_button_up()){
        delay(100); 
        page_idx_menu_program--; 
        if (page_idx_main_menu < 0){
            page_idx_main_menu = 2;
        }
    }

    if (read_button_ok()){
        delay(100); 
        menu = 0;
        index_mode = page_idx_menu_program; 
        delay(100);
    }
}

void main_menu_program(void){
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
  mc01_oled.setCursor(10, 19);
  mc01_oled.print("Program");

  // rect3
  mc01_oled.drawRoundRect(1, 31, 59, 13, 3, 1);

  // Check
  mc01_oled.setFont(NULL);
  mc01_oled.setTextColor(1);
  mc01_oled.setCursor(4, 34);
  mc01_oled.print("Configure");

  // rect4
  mc01_oled.drawRoundRect(1, 46, 59, 13, 3, 1);

  // Program
  mc01_oled.setFont(NULL);
  mc01_oled.setTextColor(1);
  mc01_oled.setCursor(16, 49);
  mc01_oled.print("Check");

  // rect5
  mc01_oled.drawRoundRect(62, 16, 65, 43, 3, 1);
  
  // Go!
  mc01_oled.setTextColor(1);
  mc01_oled.setCursor(65, 42);
  mc01_oled.setFont(&FreeSerifItalic18pt7b);
  mc01_oled.print("GO!");
  mc01_oled.display();
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
  mc01_oled.drawRoundRect(1, 16, 59, 13, 3, 1);

  // Configuration
  mc01_oled.setFont(NULL);
  mc01_oled.setTextColor(1);
  mc01_oled.setCursor(10, 19);
  mc01_oled.print("Program");

  // rect3
  mc01_oled.fillRoundRect(1, 31, 59, 13, 3, 1);

  // Check
  mc01_oled.setFont(NULL);
  mc01_oled.setTextColor(0);
  mc01_oled.setCursor(4, 34);
  mc01_oled.print("Configure");

  // rect4
  mc01_oled.drawRoundRect(1, 46, 59, 13, 3, 1);

  // Program
  mc01_oled.setFont(NULL);
  mc01_oled.setTextColor(1);
  mc01_oled.setCursor(16, 49);
  mc01_oled.print("Check");

  // rect5
  mc01_oled.drawRoundRect(62, 16, 65, 43, 3, 1);
  
  // Go!
  mc01_oled.setTextColor(1);
  mc01_oled.setCursor(65, 42);
  mc01_oled.setFont(&FreeSerifItalic18pt7b);
  mc01_oled.print("GO!");
  mc01_oled.display();
}

void main_menu_check(void){
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
  mc01_oled.drawRoundRect(1, 16, 59, 13, 3, 1);

  // Configuration
  mc01_oled.setFont(NULL);
  mc01_oled.setTextColor(1);
  mc01_oled.setCursor(10, 19);
  mc01_oled.print("Program");

  // rect3
  mc01_oled.drawRoundRect(1, 31, 59, 13, 3, 1);

  // Check
  mc01_oled.setFont(NULL);
  mc01_oled.setTextColor(1);
  mc01_oled.setCursor(4, 34);
  mc01_oled.print("Configure");

  // rect4
  mc01_oled.fillRoundRect(1, 46, 59, 13, 3, 1);

  // Program
  mc01_oled.setFont(NULL);
  mc01_oled.setTextColor(0);
  mc01_oled.setCursor(16, 49);
  mc01_oled.print("Check");

  // rect5
  mc01_oled.drawRoundRect(62, 16, 65, 43, 3, 1);
  
  // Go!
  mc01_oled.setTextColor(1);
  mc01_oled.setCursor(65, 42);
  mc01_oled.setFont(&FreeSerifItalic18pt7b);
  mc01_oled.print("GO!");
  mc01_oled.display();
}

void menu_configure(void){
    mc01_oled.clearDisplay();
    // rect_socc_4wd
    mc01_oled.fillRoundRect(1, 1, 61, 14, 3, 1);
    // str_socc_4wd
    mc01_oled.setTextColor(0);
    mc01_oled.setTextWrap(false);
    mc01_oled.setCursor(5, 5);
    mc01_oled.print("Socc 4WD");
    // rect_socc_omni
    mc01_oled.drawRoundRect(1, 17, 61, 14, 3, 1);
    // str_socc_omni
    mc01_oled.setTextColor(1);
    mc01_oled.setCursor(5, 21);
    mc01_oled.print("Socc Omni");
    // rect_socc_meca
    mc01_oled.drawRoundRect(1, 33, 61, 14, 3, 1);
    // str_socc_meca
    mc01_oled.setCursor(5, 36);
    mc01_oled.print("Socc Meca");
    // rect_ros_ddmr
    mc01_oled.drawRoundRect(1, 49, 61, 14, 3, 1);
    // str_ros_ddmr
    mc01_oled.setCursor(5, 52);
    mc01_oled.print("ROS2 DDMR");
    // rect_trans_4wd
    mc01_oled.drawRoundRect(64, 1, 63, 14, 3, 1);
    // str_trans_4wd
    mc01_oled.setCursor(66, 5);
    mc01_oled.print("Trans 4WD");
    // rect_trans_omni
    mc01_oled.drawRoundRect(64, 17, 63, 14, 3, 1);
    // str_trans_omni
    mc01_oled.setCursor(66, 21);
    mc01_oled.print("Trans Omni");
    // rect_trans_meca
    mc01_oled.drawRoundRect(64, 33, 63, 14, 3, 1);
    // str_trans_meca
    mc01_oled.setCursor(66, 36);
    mc01_oled.print("Trans Meca");
    // rect_cancel
    mc01_oled.drawRoundRect(64, 49, 40, 14, 3, 1);
    // str_cancel
    mc01_oled.setCursor(67, 52);
    mc01_oled.print("Cancel");
    // rect_ok
    mc01_oled.drawRoundRect(105, 49, 22, 14, 3, 1);
    // str_ok
    mc01_oled.setCursor(110, 53);
    mc01_oled.print("OK");
    mc01_oled.display();
}

void program_socc_4wd(void){
    mc01_oled.clearDisplay();
    // rect_socc_4wd
    mc01_oled.fillRoundRect(1, 1, 61, 14, 3, 1);
    // str_socc_4wd
    mc01_oled.setTextColor(0);
    mc01_oled.setTextWrap(false);
    mc01_oled.setCursor(5, 5);
    mc01_oled.print("Socc 4WD");
    // rect_socc_omni
    mc01_oled.drawRoundRect(1, 17, 61, 14, 3, 1);
    // str_socc_omni
    mc01_oled.setTextColor(1);
    mc01_oled.setCursor(5, 21);
    mc01_oled.print("Socc Omni");
    // rect_socc_meca
    mc01_oled.drawRoundRect(1, 33, 61, 14, 3, 1);
    // str_socc_meca
    mc01_oled.setCursor(5, 36);
    mc01_oled.print("Socc Meca");
    // rect_ros_ddmr
    mc01_oled.drawRoundRect(1, 49, 61, 14, 3, 1);
    // str_ros_ddmr
    mc01_oled.setCursor(5, 52);
    mc01_oled.print("ROS2 DDMR");
    // rect_trans_4wd
    mc01_oled.drawRoundRect(64, 1, 63, 14, 3, 1);
    // str_trans_4wd
    mc01_oled.setCursor(66, 5);
    mc01_oled.print("Trans 4WD");
    // rect_trans_omni
    mc01_oled.drawRoundRect(64, 17, 63, 14, 3, 1);
    // str_trans_omni
    mc01_oled.setCursor(66, 21);
    mc01_oled.print("Trans Omni");
    // rect_trans_meca
    mc01_oled.drawRoundRect(64, 33, 63, 14, 3, 1);
    // str_trans_meca
    mc01_oled.setCursor(66, 36);
    mc01_oled.print("Trans Meca");
    // rect_cancel
    mc01_oled.drawRoundRect(64, 49, 40, 14, 3, 1);
    // str_cancel
    mc01_oled.setCursor(67, 52);
    mc01_oled.print("Cancel");
    // rect_ok
    mc01_oled.drawRoundRect(105, 49, 22, 14, 3, 1);
    // str_ok
    mc01_oled.setCursor(110, 53);
    mc01_oled.print("OK");
    mc01_oled.display();
}

void program_socc_omni(void){
    mc01_oled.clearDisplay();
    // rect_socc_4wd
    mc01_oled.drawRoundRect(1, 1, 61, 14, 3, 1);
    // str_socc_4wd
    mc01_oled.setTextColor(1);
    mc01_oled.setTextWrap(false);
    mc01_oled.setCursor(5, 5);
    mc01_oled.print("Socc 4WD");
    // rect_socc_omni
    mc01_oled.fillRoundRect(1, 17, 61, 14, 3, 1);
    // str_socc_omni
    mc01_oled.setTextColor(0);
    mc01_oled.setCursor(5, 21);
    mc01_oled.print("Socc Omni");
    // rect_socc_meca
    mc01_oled.drawRoundRect(1, 33, 61, 14, 3, 1);
    // str_socc_meca
    mc01_oled.setTextColor(1);
    mc01_oled.setCursor(5, 36);
    mc01_oled.print("Socc Meca");
    // rect_ros_ddmr
    mc01_oled.drawRoundRect(1, 49, 61, 14, 3, 1);
    // str_ros_ddmr
    mc01_oled.setCursor(5, 52);
    mc01_oled.print("ROS2 DDMR");
    // rect_trans_4wd
    mc01_oled.drawRoundRect(64, 1, 63, 14, 3, 1);
    // str_trans_4wd
    mc01_oled.setCursor(66, 5);
    mc01_oled.print("Trans 4WD");
    // rect_trans_omni
    mc01_oled.drawRoundRect(64, 17, 63, 14, 3, 1);
    // str_trans_omni
    mc01_oled.setCursor(66, 21);
    mc01_oled.print("Trans Omni");
    // rect_trans_meca
    mc01_oled.drawRoundRect(64, 33, 63, 14, 3, 1);
    // str_trans_meca
    mc01_oled.setCursor(66, 36);
    mc01_oled.print("Trans Meca");
    // rect_cancel
    mc01_oled.drawRoundRect(64, 49, 40, 14, 3, 1);
    // str_cancel
    mc01_oled.setCursor(67, 52);
    mc01_oled.print("Cancel");
    // rect_ok
    mc01_oled.drawRoundRect(105, 49, 22, 14, 3, 1);
    // str_ok
    mc01_oled.setCursor(110, 53);
    mc01_oled.print("OK");
    mc01_oled.display();
}

void program_socc_meca(void){
    mc01_oled.clearDisplay();
    // rect_socc_4wd
    mc01_oled.drawRoundRect(1, 1, 61, 14, 3, 1);
    // str_socc_4wd
    mc01_oled.setTextColor(1);
    mc01_oled.setTextWrap(false);
    mc01_oled.setCursor(5, 5);
    mc01_oled.print("Socc 4WD");
    // rect_socc_omni
    mc01_oled.drawRoundRect(1, 17, 61, 14, 3, 1);
    // str_socc_omni
    mc01_oled.setCursor(5, 21);
    mc01_oled.print("Socc Omni");
    // rect_socc_meca
    mc01_oled.fillRoundRect(1, 33, 61, 14, 3, 1);
    // str_socc_meca
    mc01_oled.setTextColor(0);
    mc01_oled.setCursor(5, 36);
    mc01_oled.print("Socc Meca");
    // rect_ros_ddmr
    mc01_oled.drawRoundRect(1, 49, 61, 14, 3, 1);
    // str_ros_ddmr
    mc01_oled.setTextColor(1);
    mc01_oled.setCursor(5, 52);
    mc01_oled.print("ROS2 DDMR");
    // rect_trans_4wd
    mc01_oled.drawRoundRect(64, 1, 63, 14, 3, 1);
    // str_trans_4wd
    mc01_oled.setCursor(66, 5);
    mc01_oled.print("Trans 4WD");
    // rect_trans_omni
    mc01_oled.drawRoundRect(64, 17, 63, 14, 3, 1);
    // str_trans_omni
    mc01_oled.setCursor(66, 21);
    mc01_oled.print("Trans Omni");
    // rect_trans_meca
    mc01_oled.drawRoundRect(64, 33, 63, 14, 3, 1);
    // str_trans_meca
    mc01_oled.setCursor(66, 36);
    mc01_oled.print("Trans Meca");
    // rect_cancel
    mc01_oled.drawRoundRect(64, 49, 40, 14, 3, 1);
    // str_cancel
    mc01_oled.setCursor(67, 52);
    mc01_oled.print("Cancel");
    // rect_ok
    mc01_oled.drawRoundRect(105, 49, 22, 14, 3, 1);
    // str_ok
    mc01_oled.setCursor(110, 53);
    mc01_oled.print("OK");
    mc01_oled.display();
}

void program_ros2_ddmr(void){
    
}

void program_trans_4wd(void){
    
}

void program_trans_omni(void){

}

void program_trans_meca(void){
    
}

