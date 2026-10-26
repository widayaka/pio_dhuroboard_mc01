#ifndef __MOTOR_H__
#define __MOTOR_H__

#define PWM_PIN_1A  23  
#define PWM_PIN_1B  19
#define PWM_PIN_2A  18
#define PWM_PIN_2B  4

#define CW 0
#define CCW 1

extern int frequency;
extern int resolution;
extern int pwmChannel1;
extern int pwmChannel2;

void init_mc01_motor(void);
void driveMotor1(int pwm);
void driveMotor2(int pwm);

#endif