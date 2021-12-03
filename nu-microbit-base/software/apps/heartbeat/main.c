// main for heartbeat interrupts
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "heartbeat.h"
#include <nrf_lpcomp.h>

int main(void){

    // intialize drivers

    // USE NRFX

    // initialize 
    lpcomp_init();

    nrf_lpcomp_int_enable(-1);

    // loop forever
    while (1) {
        if (nrf_lpcomp_int_enable_check(-1)){
            printf("Beat!\n");
        }
    }

    return 0;
}
