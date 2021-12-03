#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "app_timer.h"
#include <math.h>

#include "nrf_delay.h"
#include "nrf_twi_mngr.h"

#include "microbit_v2.h"
#include "oledtwi.h"

// Global variables
NRF_TWI_MNGR_DEF(twi_mngr_instance, 1, 0);
APP_TIMER_DEF(my_timer_1);

int main(void)
{
    printf("Board started!\n");

    // Initialize I2C peripheral and driver
    nrf_drv_twi_config_t i2c_config = NRF_DRV_TWI_DEFAULT_CONFIG;
    i2c_config.scl = EDGE_P19;
    i2c_config.sda = EDGE_P20;
    i2c_config.frequency = NRF_TWIM_FREQ_100K;
    i2c_config.interrupt_priority = 0;
    nrf_twi_mngr_init(&twi_mngr_instance, &i2c_config);

    // Loop forever
    while (1)
    {
        // Don't put any code in here. Instead put periodic code in a callback using a timer.
        nrf_delay_ms(1000);
    }
}
