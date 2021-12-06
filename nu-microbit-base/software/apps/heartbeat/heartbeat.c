
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrfx_lpcomp.h"
#include "nrf_lpcomp.h"

#include "heartbeat.h"

void lpcomp_init(){

    nrf_lpcomp_config_t hal_ = {
        .detection = NRF_LPCOMP_DETECT_UP,
        .reference = NRF_LPCOMP_REF_SUPPLY_7_8
    };

    nrf_lpcomp_input_t input_ = NRF_LPCOMP_INPUT_3;

    const nrfx_lpcomp_config_t p_config = {
        .hal = hal_, 
        .input = input_,
        .interrupt_priority = 1
    };

    static void event_handler(nrfx_lpcomp_event_handler_t const * p_event) {
        printf("Bing Bong!\n");
    }

    nrfx_lpcomp_init(&p_config, event_handler);

}



