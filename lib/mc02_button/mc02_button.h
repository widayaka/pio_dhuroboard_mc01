#ifndef __GPIO_H__
#define __GPIO_H__

#define BUTTON_UP 12
#define BUTTON_DN 15
#define BUTTON_OK 2

extern bool button_up;
extern bool button_dn;
extern bool button_ok;

void setup_button(void);
bool read_button_up();
bool read_button_dn();
bool read_button_ok();

#endif