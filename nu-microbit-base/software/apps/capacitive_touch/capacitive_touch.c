// Capacitive touch library
// Detects touch status of the logo touchpad

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "app_timer.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrfx_gpiote.h"
#include "nrfx_timer.h"

#include "microbit_v2.h"

#include "capacitive_touch.h"

APP_TIMER_DEF(touch_timer);

// High-speed timer for timeout detection
static nrfx_timer_t TIMER4 = NRFX_TIMER_INSTANCE(0);

// Status of the touch sensor
static bool touch_active = false;
static bool timer_int = false;

// Callback function for GPIO interrupts
static void gpio_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action) {
	// Low to high
	//printf("%lu\n", nrfx_timer_capture(&TIMER4, 0));	
	//printf("No touch_handle\n");
	nrfx_timer_pause(&TIMER4);
	nrfx_gpiote_in_event_disable(TOUCH_LOGO);
	//printf("PAUSE: %lu\n",nrfx_timer_capture(&TIMER4, 0));
	//nrfx_gpiote_in_event_disable(TOUCH_LOGO);
}

static void timer_handler(nrf_timer_event_t event, void* context) {
  //printf("Touch_handle: %lu\n",nrfx_timer_capture(&TIMER4, 0));
  //timer_int = true;
  nrfx_timer_pause(&TIMER4);
  timer_int = true;
  //printf("Touch_handle: %lu\n",nrfx_timer_capture(&TIMER4, 0));
  nrfx_gpiote_in_event_disable(TOUCH_LOGO);
}

// Helper function for starting a test
// A "capacitive test" consists of:
//  1. Driving the pad low
//  2. Changing to an input and allowing it to float high
//  3. Either triggering a GPIO interrupt when it becomes high or timing out
static void start_capacitive_test(void *_unused) {
  // set pin as input and clear it
  nrf_gpio_cfg(TOUCH_LOGO, NRF_GPIO_PIN_DIR_OUTPUT, NRF_GPIO_PIN_INPUT_DISCONNECT,
      NRF_GPIO_PIN_NOPULL, NRF_GPIO_PIN_S0S1, NRF_GPIO_PIN_NOSENSE);
  nrf_gpio_pin_clear(TOUCH_LOGO);

  touch_active = timer_int;
  timer_int = false;

  // clear and resume timeout timer
  nrfx_timer_clear(&TIMER4);
  nrfx_timer_resume(&TIMER4);

  // re-initialize and enable GPIO interrupt event
  nrfx_gpiote_in_config_t in_config = NRFX_GPIOTE_CONFIG_IN_SENSE_LOTOHI(true); // high-accuracy mode
  nrfx_gpiote_in_init(TOUCH_LOGO, &in_config, gpio_handler);
  nrfx_gpiote_in_event_enable(TOUCH_LOGO, true); // enable interrupts
}

// Starts continuously measuring capacitive touch for the logo
// Function returns immediately without blocking
void capacitive_touch_init(void) {
  // configure high-speed timer
  // timer should be 1 MHz and 32-bit
  nrfx_timer_config_t timer_config = {
    .frequency = NRF_TIMER_FREQ_1MHz,
    .mode = NRF_TIMER_MODE_TIMER,
    .bit_width = NRF_TIMER_BIT_WIDTH_32,
    .interrupt_priority = 4,
    .p_context = NULL
  };
  nrfx_timer_init(&TIMER4, &timer_config, timer_handler);

  // Set Compare Register
  nrfx_timer_compare(&TIMER4, 1, 1000, true);

  // enable, but pause the timer
  nrfx_timer_enable(&TIMER4);
  nrfx_timer_pause(&TIMER4);


  // Initialize app timer
  app_timer_init();
  app_timer_create(&touch_timer, APP_TIMER_MODE_REPEATED, start_capacitive_test);

  // start timer
  // change the rate to whatever you want
  app_timer_start(touch_timer, 1500, NULL);


  // start the touch test
  //start_capacitive_test();
}

// Determines whether the logo is being touched
//	True means the logo is being touched
//	False means the logo is not being touched
//
// Function returns immediately without blocking
bool capacitive_touch_is_active(void) {
  // return latest reading from the capacitive touch sensor
  return touch_active;
}

