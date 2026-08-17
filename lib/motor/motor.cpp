#include <Arduino.h>
#include "motor.h"

int frequency = 5000;
int resolution = 8;
int pwmChannel1 = 0;
int pwmChannel2 = 1;

void setup_motor(){
    ledcSetup(pwmChannel1, frequency, resolution);
    ledcAttachPin(PWM_PIN_1A, pwmChannel1); pinMode(PWM_PIN_1B, OUTPUT);
    ledcSetup(pwmChannel2, frequency, resolution);
    ledcAttachPin(PWM_PIN_2A, pwmChannel2); pinMode(PWM_PIN_2B, OUTPUT);
}