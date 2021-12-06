#pragma once

#include "nrf_twi_mngr.h"
#include <math.h>

static const uint8_t PAGE = 0;
static const uint8_t ALL = 1;

static const uint8_t I2C_COMMAND = 0x00;
static const uint8_t I2C_DATA = 0x40;

static const uint8_t SETCONTRAST = 0x81;
static const uint8_t DISPLAYALLONRESUME = 0xA4;
static const uint8_t DISPLAYALLON = 0xA5;
static const uint8_t NORMALDISPLAY = 0xA6;
static const uint8_t INVERTDISPLAY = 0xA7;
static const uint8_t DISPLAYOFF = 0xAE;
static const uint8_t DISPLAYON = 0xAF;
static const uint8_t SETDISPLAYOFFSET = 0xD3;
static const uint8_t SETCOMPINS = 0xDA;
static const uint8_t SETVCOMDESELECT = 0xDB;
static const uint8_t SETDISPLAYCLOCKDIV = 0xD5;
static const uint8_t SETPRECHARGE = 0xD9;
static const uint8_t SETMULTIPLEX = 0xA8;
static const uint8_t SETLOWCOLUMN = 0x00;
static const uint8_t SETHIGHCOLUMN = 0x10;
static const uint8_t SETSTARTLINE = 0x40;
static const uint8_t MEMORYMODE = 0x20;
static const uint8_t COMSCANINC = 0xC0;
static const uint8_t COMSCANDEC = 0xC8;
static const uint8_t SEGREMAP = 0xA0;
static const uint8_t CHARGEPUMP = 0x8D;
static const uint8_t EXTERNALVCC = 0x01;
static const uint8_t SWITCHCAPVCC = 0x02;

// Peripheral address for the OLED Display
static const uint8_t DISPLAY_ADDRESS = 0x3D;

static const uint8_t DISPLAY_WRITE_0 = 0x78;
static const uint8_t DISPLAY_READ_0 = 0x79;

static const uint8_t DISPLAY_WRITE_1 = 0x7A;
static const uint8_t DISPLAY_READ_1 = 0x7B;

void oledtwi_init(void);
