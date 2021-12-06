#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "oledtwi.h"
#include "nrf_delay.h"

static uint8_t screenbuffer[8 * 128];
const uint8_t LCDHEIGHT_ = 64;
const uint8_t LCDWIDTH_ = 128;

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

    };
    nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer, 2, NULL);

    return rx_buf;
}

// Helper function to perform a 1-byte I2C write of a given register
//
// i2c_addr - address of the device to write to
// reg_addr - address of the register within the device to write
static void i2c_reg_write(uint8_t i2c_addr, uint8_t control_byte, uint8_t data)
{

    uint8_t writeAdrs[2] = {control_byte, data};
    nrf_twi_mngr_transfer_t const write_transfer[] = {

        NRF_TWI_MNGR_WRITE(i2c_addr, writeAdrs, 2, 0)};

    nrf_twi_mngr_perform(i2c_manager, NULL, write_transfer, 1, NULL);

    //Note: there should only be a single two-byte transfer to be performed
}

void oledtwi_init()
{
    uint8_t initArr[46] = {I2C_COMMAND,
                           DISPLAYOFF,
                           I2C_COMMAND,
                           SETDISPLAYCLOCKDIV,
                           I2C_COMMAND,
                           0x80,
                           I2C_COMMAND,
                           SETMULTIPLEX,
                           I2C_COMMAND,
                           LCDHEIGHT_ - 1,
                           I2C_COMMAND,
                           SETDISPLAYOFFSET,
                           I2C_COMMAND,
                           0x0,
                           I2C_COMMAND,
                           SETSTARTLINE | 0x0,
                           I2C_COMMAND,
                           CHARGEPUMP,
                           I2C_COMMAND,
                           0x14,
                           I2C_COMMAND,
                           NORMALDISPLAY,
                           I2C_COMMAND,
                           DISPLAYALLONRESUME,
                           I2C_COMMAND,
                           SEGREMAP | 0x1,
                           I2C_COMMAND,
                           COMSCANDEC,
                           I2C_COMMAND,
                           SETCOMPINS,
                           I2C_COMMAND,
                           0x12, // try changing to 0x02 if it doesn't work
                           I2C_COMMAND,
                           SETCONTRAST,
                           I2C_COMMAND,
                           0x8F,
                           I2C_COMMAND,
                           SETPRECHARGE,
                           I2C_COMMAND,
                           0x22,
                           I2C_COMMAND,
                           SETVCOMDESELECT,
                           I2C_COMMAND,
                           0x30,
                           I2C_COMMAND,
                           DISPLAYON};

    nrf_twi_mngr_transfer_t const write_transfer[] = {
            NRF_TWI_MNGR_WRITE(0x3D, initArr, 46, 0)
    };

    nrf_twi_mngr_perform(i2c_manager, NULL, write_transfer, 1, NULL);
}