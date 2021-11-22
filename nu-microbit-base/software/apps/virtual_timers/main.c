// Virtual timers
//
// Uses a single hardware timer to create an unlimited supply of virtual
//  software timers

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "app_error.h"
#include "app_timer.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_serial.h"

#include "microbit_v2.h"
#include "virtual_timer.h"
// GET RID OF THIS
#include "virtual_timer_linked_list.h"

void led1_toggle() {
    nrf_gpio_pin_toggle(LED_ROW1);
}

void led2_toggle() {
    nrf_gpio_pin_toggle(LED_ROW2);
}

void led3_toggle() {
    nrf_gpio_pin_toggle(LED_ROW3);
}

int main(void) {
  printf("Board initialized!\n");

  // Configure Microbit pins
  nrf_gpio_pin_dir_set(LED_COL1, NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_dir_set(LED_ROW1, NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_dir_set(LED_ROW2, NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_dir_set(LED_ROW3, NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_clear(LED_COL1);
  nrf_gpio_pin_clear(LED_ROW1);
  nrf_gpio_pin_clear(LED_ROW2);
  nrf_gpio_pin_clear(LED_ROW3);

  // Initialize your timer library
  virtual_timer_init();
  nrf_delay_ms(3000);
  // uint32_t id = virtual_timer_start_repeated(1000000, led1_toggle);


  // Setup some timers and see what happens
  uint32_t one_sec_flash = virtual_timer_start_repeated(1000000, led1_toggle);
  uint32_t two_sec_flash = virtual_timer_start_repeated(2000000, led2_toggle);
  uint32_t four_sec_flash = virtual_timer_start_repeated(4000000, led3_toggle);

  // loop forever
  uint32_t sixteen_sec = read_timer() + 16000000;
  uint32_t twenty_sec = read_timer() + 20000000;
  while (1) {
    if (read_timer() > twenty_sec) {
      virtual_timer_cancel(one_sec_flash);
    }
    if (read_timer() > sixteen_sec) {
      virtual_timer_cancel(two_sec_flash);
      virtual_timer_cancel(four_sec_flash);
    }
    nrf_delay_ms(500);
    printf("%lu\n", read_timer());
    list_print();
  }
}

