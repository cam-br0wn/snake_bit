// main for heartbeat interrupts

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "app_timer.h"
#include "nrf_delay.h"
#include "nrfx_lpcomp.h"

#include "microbit_v2.h"
#include "heartbeat.h"

int main(void) {
  printf("Board started!\n");

  // intialize drivers
  nrfx_lpcomp_init(&p_config, event_handler);
  app_timer_init();
  
  // start capacitive touch driver
  lpcomp_init();

  // loop forever
  while (1) {
      
  }
}
