#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <SPI.h>
#include <Wire.h>
#include <Arduino.h>
#include "Adafruit_SSD1306.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

extern Adafruit_SSD1306 mc01_oled;

extern int menu;
extern int pilih_menu;
extern int pilih_mode;

void templateMainMenu(void);
void drawMainMenu(int selected);
void mainMenu(void);

void main_menu_configure(void);

#endif