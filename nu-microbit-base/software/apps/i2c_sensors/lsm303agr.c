// LSM303AGR driver for Microbit_v2
//
// Initializes sensor and communicates over I2C
// Capable of reading temperature, acceleration, and magnetic field strength

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "lsm303agr.h"
#include "nrf_delay.h"

// Pointer to an initialized I2C instance to use for transactions
static const nrf_twi_mngr_t* i2c_manager = NULL;

// Helper function to perform a 1-byte I2C read of a given register
//
// i2c_addr - address of the device to read from
// reg_addr - address of the register within the device to read
//
// returns 8-bit read value
static uint8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr) {
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
static void i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t data) {
  //TODO: implement me
    uint8_t writeAdrs [2] = {reg_addr, data};
    nrf_twi_mngr_transfer_t const write_transfer[] = {
    
    NRF_TWI_MNGR_WRITE(i2c_addr, writeAdrs, 2, 0)
    };

  nrf_twi_mngr_perform(i2c_manager, NULL, write_transfer, 1, NULL);

  //Note: there should only be a single two-byte transfer to be performed
}

// Initialize and configure the LSM303AGR accelerometer/magnetometer
//
// i2c - pointer to already initialized and enabled twim instance
void lsm303agr_init(const nrf_twi_mngr_t* i2c) {
  i2c_manager = i2c;

  // ---Initialize Accelerometer---

  // Reboot acclerometer
  i2c_reg_write(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_CTRL_REG5, 0x80);
  nrf_delay_ms(100); // needs delay to wait for reboot

  // Enable Block Data Update
  // Only updates sensor data when both halves of the data has been read
  i2c_reg_write(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_CTRL_REG4, 0x80);

  // Configure accelerometer at 100Hz, normal mode (10-bit)
  // Enable x, y and z axes
  i2c_reg_write(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_CTRL_REG1, 0x57);

  // Read WHO AM I register
  // Always returns the same value if working
  uint8_t result = i2c_reg_read(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_WHO_AM_I_REG);
  //TODO: check the result of the Accelerometer WHO AM I register
  printf("Accelerometer: %x\n", result);
  // ---Initialize Magnetometer---

  // Reboot magnetometer
  i2c_reg_write(LSM303AGR_MAG_ADDRESS, LSM303AGR_MAG_CFG_REG_A, 0x40);
  nrf_delay_ms(100); // needs delay to wait for reboot

  // Enable Block Data Update
  // Only updates sensor data when both halves of the data has been read
  i2c_reg_write(LSM303AGR_MAG_ADDRESS, LSM303AGR_MAG_CFG_REG_C, 0x10);

  // Configure magnetometer at 100Hz, continuous mode
  i2c_reg_write(LSM303AGR_MAG_ADDRESS, LSM303AGR_MAG_CFG_REG_A, 0x0C);

  // Read WHO AM I register
  result = i2c_reg_read(LSM303AGR_MAG_ADDRESS, LSM303AGR_MAG_WHO_AM_I_REG);
  printf("Magnetometer: %x\n", result);
  //TODO: check the result of the Magnetometer WHO AM I register

  // ---Initialize Temperature---

  // Enable temperature sensor
  i2c_reg_write(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_TEMP_CFG_REG, 0xC0);
}

// Read the internal temperature sensor

// Return measurement as floating point value in degrees C
float lsm303agr_read_temperature(void) {

  uint8_t low = i2c_reg_read(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_TEMP_L);
  uint8_t high = i2c_reg_read(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_TEMP_H);
  uint16_t hTemp = high;
  hTemp = hTemp << 8;
  uint16_t lTemp = low;
  int16_t resultTemp = hTemp | lTemp;
  float finalTemp = (float)resultTemp*1.0/256.0 + 25.0;
  return finalTemp;
}

lsm303agr_measurement_t lsm303agr_read_accelerometer(void) {
  uint8_t xL = i2c_reg_read(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_OUT_X_L);
  uint8_t xH = i2c_reg_read(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_OUT_X_H);
  uint8_t yL = i2c_reg_read(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_OUT_Y_L);
  uint8_t yH = i2c_reg_read(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_OUT_Y_H);
  uint8_t zL = i2c_reg_read(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_OUT_Z_L);
  uint8_t zH = i2c_reg_read(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_OUT_Z_H);

  uint16_t xHigh = xH;
  xHigh = xHigh << 8;
  uint16_t xLow = xL;
  int16_t xResult = xHigh | xLow;
  xResult = xResult >> 6;
  float xResultf = (float)xResult * 3.9 / 1000;

  uint16_t yHigh = yH;
  yHigh = yHigh << 8;
  uint16_t yLow = yL;
  int16_t yResult = yHigh | yLow;
  yResult = yResult >> 6;
  float yResultf = (float)yResult * 3.9 / 1000;

  uint16_t zHigh = zH;
  zHigh = zHigh << 8;
  uint16_t zLow = zL;
  int16_t zResult = zHigh | zLow;
  zResult = zResult >> 6;
  float zResultf = (float)zResult * 3.9 / 1000;


  lsm303agr_measurement_t measurement = {xResultf, yResultf, zResultf};
  // measurement->x_axis = xResultf;
  // measurement->y_axis = yResultf;
  // measurement->z_axis = zResultf;
  return measurement;
}

lsm303agr_measurement_t lsm303agr_read_magnetometer(void) {
  uint8_t xL = i2c_reg_read(LSM303AGR_MAG_ADDRESS, LSM303AGR_MAG_OUT_X_L_REG);
  uint8_t xH = i2c_reg_read(LSM303AGR_MAG_ADDRESS, LSM303AGR_MAG_OUT_X_H_REG);
  uint8_t yL = i2c_reg_read(LSM303AGR_MAG_ADDRESS, LSM303AGR_MAG_OUT_Y_L_REG);
  uint8_t yH = i2c_reg_read(LSM303AGR_MAG_ADDRESS, LSM303AGR_MAG_OUT_Y_H_REG);
  uint8_t zL = i2c_reg_read(LSM303AGR_MAG_ADDRESS, LSM303AGR_MAG_OUT_Z_L_REG);
  uint8_t zH = i2c_reg_read(LSM303AGR_MAG_ADDRESS, LSM303AGR_MAG_OUT_Z_H_REG);

  uint16_t xHigh = xH;
  xHigh = xHigh << 8;
  uint16_t xLow = xL;
  int16_t xResult = xHigh | xLow;
  float xResultf = (float)xResult * 1.5 / 10;

  uint16_t yHigh = yH;
  yHigh = yHigh << 8;
  uint16_t yLow = yL;
  int16_t yResult = yHigh | yLow;
  float yResultf = (float)yResult * 1.5 / 10;

  uint16_t zHigh = zH;
  zHigh = zHigh << 8;
  uint16_t zLow = zL;
  int16_t zResult = zHigh | zLow;
  float zResultf = (float)zResult * 1.5 / 10;


  lsm303agr_measurement_t mag_measurement = {xResultf, yResultf, zResultf};

  return mag_measurement;
}

float read_tilt_angle(void) {
  lsm303agr_measurement_t accel_measurement = lsm303agr_read_accelerometer();
  float x_axis = accel_measurement.x_axis;
  float y_axis = accel_measurement.y_axis;
  float z_axis = accel_measurement.z_axis;

  return atan(sqrt(pow(x_axis, 2.0) + pow(y_axis, 2.0))/(z_axis)) * (180.0 / M_PI);
}

void read_everything(void) {
  printf("Temp: %f\n", lsm303agr_read_temperature());

  lsm303agr_measurement_t accel_measurement = lsm303agr_read_accelerometer();
  printf("Accel x: %f\n", accel_measurement.x_axis);
  printf("Accel y: %f\n", accel_measurement.y_axis);
  printf("Accel z: %f\n", accel_measurement.z_axis);

  lsm303agr_measurement_t mag_measurement = lsm303agr_read_magnetometer();
  printf("Mag x: %f\n", mag_measurement.x_axis);
  printf("Mag y: %f\n", mag_measurement.y_axis);
  printf("Mag z: %f\n", mag_measurement.z_axis);

  printf("Tilt angle: %f\n", read_tilt_angle());
}



