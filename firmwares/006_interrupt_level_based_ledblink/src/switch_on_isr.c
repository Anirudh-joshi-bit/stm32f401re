#include "../include/commons.h"
extern uint32_t delay_mag;
extern uint32_t delay_mag_original;
extern uint32_t levels;
extern bool on_board_switch_falling;


void switch_on_isr(void) {

    if (levels == 5){
        delay_mag = delay_mag_original;
        levels = 1;
        return;
    }
    levels++;
    delay_mag -= 100000;
}
