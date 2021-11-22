// LED Matrix app
//
// Display messages on the LED matrix

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf_delay.h"

#include "led_matrix.h"
#include "microbit_v2.h"


int main(void) {
  printf("Board started!\n");
  
  led_matrix_init();
  char msg1[] = "Hi CE346!";
  char msg2[] = "It works!";
  draw_string(msg1, 0);
  nrf_delay_ms(15000);
  draw_string(msg2, 1);

  // loop forever
  while (1) {
    nrf_delay_ms(1000);
  }
}

