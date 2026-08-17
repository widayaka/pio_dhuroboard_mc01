#ifndef __MOTOR_H__
#define __MOTOR_H__

#define PWM_PIN_1A  23  
#define PWM_PIN_1B  19
#define PWM_PIN_2A  18
#define PWM_PIN_2B  4

extern int frequency;
extern int resolution;
extern int pwmChannel1;
extern int pwmChannel2;

void setup_motor(void);

#endif