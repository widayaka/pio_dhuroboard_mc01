#include <Arduino.h>
#include "mc01_encoder.h"

int VAL_ENC_1A = 0;
int VAL_ENC_1B = 0;
int VAL_ENC_2A = 0;
int VAL_ENC_2B = 0;

int interval = 10;
unsigned long currentTime = 0;
unsigned long previousTime = 0;

float delta_counter;

encoder_data encoder[NUM_OF_MOTORS] = {};

void encoder1_ISR(void){
    VAL_ENC_1A = digitalRead(ENCODER1A);
    VAL_ENC_1B = digitalRead(ENCODER1B);
    if ((VAL_ENC_1A == HIGH) != (VAL_ENC_1B == LOW)){encoder->counter[0]++;}
    else{encoder->counter[0]--;}
}

void encoder2_ISR(void){
    VAL_ENC_2A = digitalRead(ENCODER2A);
    VAL_ENC_2B = digitalRead(ENCODER2B);
    if ((VAL_ENC_2A == HIGH) != (VAL_ENC_2B == LOW)){encoder->counter[1]++;}
    else{encoder->counter[1]--;}
}

void init_mc01_encoder(){
    attachInterrupt(digitalPinToInterrupt(ENCODER1A), encoder1_ISR, CHANGE); pinMode(ENCODER1B, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENCODER2A), encoder2_ISR, CHANGE); pinMode(ENCODER2B, INPUT);
    for (int i=0;i<NUM_OF_MOTORS;i++) encoder->counter[i]=0;
}

void encoder_calculation(){
    currentTime = millis();
    if (currentTime - previousTime >= interval){
        previousTime = currentTime;
        float dt = interval / 1000.0f;
        for (int i=0;i<NUM_OF_MOTORS;i++){
            delta_counter = encoder->counter[i] - encoder->previous_counter[i];
            encoder->rpm_motor[i] = (delta_counter * 60) / ((ENCODER_PPR * ENCODER_QUADRATURE) * dt);
            encoder->rpm_gearbox[i] = (delta_counter * 60) / ((ENCODER_PPR * ENCODER_QUADRATURE * GEARBOX_RATIO) * dt);
            encoder->previous_counter[i] = encoder->counter[i];
        }
    }
}