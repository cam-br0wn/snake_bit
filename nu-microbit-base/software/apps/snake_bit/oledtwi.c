#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "oledtwi.h"
#include "nrf_delay.h"

static uint8_t _screenbuffer[8 * 128];

// Pointer to an initialized I2C instance to use for transactions
static const nrf_twi_mngr_t *i2c_manager = NULL;

// Helper function to perform a 1-byte I2C read of a given register
//
// i2c_addr - address of the device to read from
// reg_addr - address of the register within the device to read
//
// returns 8-bit read value
static uint8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr)
{
    uint8_t rx_buf = 0;
    nrf_twi_mngr_transfer_t const read_transfer[] = {
        // .transWrite =
        NRF_TWI_MNGR_WRITE(i2c_addr, &reg_addr, 1, NRF_TWI_MNGR_NO_STOP),

        // .transRead =
        NRF_TWI_MNGR_READ(i2c_addr, &rx_buf, 1, 0)
        //TODO: implement me
    };
    nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer, 2, NULL);

    return rx_buf;
}

// Helper function to perform a 1-byte I2C write of a given register
//
// i2c_addr - address of the device to write to
// reg_addr - address of the register within the device to write
static void i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t data)
{
    //TODO: implement me
    uint8_t writeAdrs[2] = {reg_addr, data};
    nrf_twi_mngr_transfer_t const write_transfer[] = {

        NRF_TWI_MNGR_WRITE(i2c_addr, writeAdrs, 2, 0)};

    nrf_twi_mngr_perform(i2c_manager, NULL, write_transfer, 1, NULL);

    //Note: there should only be a single two-byte transfer to be performed
}

void oledtwi_init()
{
}