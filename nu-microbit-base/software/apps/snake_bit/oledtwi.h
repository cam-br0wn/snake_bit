#pragma once

#include "nrf_twi_mngr.h"

// Peripheral address for the OLED Display
static const uint8_t DISPLAY_ADDRESS = 0x3D;

static const uint8_t DISPLAY_WRITE_0 = 0x78;
static const uint8_t DISPLAY_READ_0 = 0x79;

static const uint8_t DISPLAY_WRITE_1 = 0x7A;
static const uint8_t DISPLAY_READ_1 = 0x7B;
