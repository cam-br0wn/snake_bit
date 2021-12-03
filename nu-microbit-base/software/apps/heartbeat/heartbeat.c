
#include <nrf_lpcomp.h>

void lpcomp_init(){
    const nrf_lpcomp_config_t lpcomp_config = {
        .detection = NRF_LPCOMP_DETECT_UP,
        .reference = NRF_LPCOMP_REF_SUPPLY_7_8
    };

    // first configure the LPCOMP
    nrf_lpcomp_configure(&lpcomp_config);

    // pin select 3
    nrf_lpcomp_input_select(NRF_LPCOMP_INPUT_3);

    nrf_lpcomp_enable();
}



