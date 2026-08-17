#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <stdint.h>

#define ENCODER1A   36
#define ENCODER1B   39
#define ENCODER2A   34
#define ENCODER2B   35

#define NUM_OF_MOTORS 2

#define ENCODER_PPR 11
#define ENCODER_QUADRATURE 2
#define GEARBOX_RATIO 46.0

extern int VAL_ENC_1A;
extern int VAL_ENC_1B;
extern int VAL_ENC_2A;
extern int VAL_ENC_2B;

extern int interval;
extern unsigned long currentTime;
extern unsigned long previousTime;

extern float delta_counter;

struct encoder_data
{
    int32_t counter[NUM_OF_MOTORS];
    int32_t previous_counter[NUM_OF_MOTORS];
    int32_t encoder_last_cnt[NUM_OF_MOTORS];
    int32_t rpm_motor[NUM_OF_MOTORS];
    int32_t rpm_gearbox[NUM_OF_MOTORS];
};

extern encoder_data encoder[NUM_OF_MOTORS];

void encoder1_ISR(void);
void encoder2_ISR(void);
void setup_encoder(void);
void encoder_calculation(void);

#endif