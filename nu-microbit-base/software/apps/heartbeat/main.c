// main for heartbeat interrupts
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "heartbeat.h"
#include "nrf_delay.h"

int main(void){

    // intialize drivers
    nrfx_gpiote_init();
    app_timer_init();

    lpcomp_init();

    // loop forever
    while (1) {
        if (nrf_lpcomp_int_enable_check(-1)){
            printf("Beat!\n");
        }
    }

    return 0;
}
