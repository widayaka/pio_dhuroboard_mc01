
#include <Arduino.h>
#include "gpio.h"

bool button_up = false;
bool button_dn = false;
bool button_ok = false;

void setup_button(){
    pinMode(BUTTON_UP, INPUT_PULLUP);
    pinMode(BUTTON_DN, INPUT_PULLUP);
    pinMode(BUTTON_OK, INPUT_PULLUP);
}

bool read_button_up(){
    button_up = !digitalRead(BUTTON_UP);
    return button_up;
}

bool read_button_dn(){
    button_dn = !digitalRead(BUTTON_DN);
    return button_dn;
}

bool read_button_ok(){
    button_ok = !digitalRead(BUTTON_OK);
    return button_ok;
}