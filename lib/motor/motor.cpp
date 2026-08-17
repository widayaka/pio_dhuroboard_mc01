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

void driveMotor1(int pwm){
    int dir;  dir = pwm > 0 ? CW : CCW;
    
    if (pwm > 255) pwm = 255;
    else if (pwm < 0) {pwm = -pwm; pwm = 255 - pwm;}
    else if (pwm == 0) {pwm = pwm; dir = 0;}
    
    ledcWrite(pwmChannel1, pwm); digitalWrite(PWM_PIN_1B, dir);
  }
  
  void driveMotor2(int pwm){
    int dir; dir = pwm > 0 ? CW : CCW;
    
    if (pwm > 255) pwm = 255;
    else if (pwm < 0) {pwm = -pwm; pwm = 255 - pwm;}
    else if (pwm == 0) {pwm = pwm; dir = 0;}
    
    ledcWrite(pwmChannel2, pwm); digitalWrite(PWM_PIN_2B, dir);
  }