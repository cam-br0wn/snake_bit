// GPIO app
//
// Uses MMIO to control GPIO pins

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf.h"
#include "nrf_delay.h"

#include "microbit_v2.h"
#include "gpio.h"

int main(void) {
  printf("Board started!\n"); 

  printf("%d\n", 20 | 52);

  NRF_GPIOTE->CONFIG[0] = 0x00020E01;
  NVIC_EnableIRQ(GPIOTE_IRQn);
  NVIC_SetPriority(GPIOTE_IRQn, 0);
  
  NVIC_EnableIRQ(SWI1_EGU1_IRQn);
  NVIC_SetPriority(SWI1_EGU1_IRQn, 1);


  // Step 2:
  // Control LED with raw MMIO
  // Microphone LED is P0.20 and active high
  // Add code here
  *(uint32_t*)(0x50000514) = 1 << 20;
  *(uint32_t*)(0x50000504) = 1 << 20;
  // loop forever
  printf("Looping\n");
  while (1) {

    // Step 4:
    // Control LED with buttons
    // Button A is P0.14 and active low
    // Button B is P0.23 and active low
    // Add code here
    // gpio_config(14, 0);
    // gpio_config(23, 0);
    // gpio_config(20, 1);
    // uint8_t fourteen = 14;
    // uint8_t twentythree = 23;
    // uint8_t twenty = 20;

    // if (!gpio_read(fourteen)) {

	  //   printf("Button A Pressed!");
	  //   gpio_set(twenty);
    // }

    // if (!gpio_read(twentythree)) {

	  //   printf("Button B Pressed!");
	  //   gpio_clear(twenty);

    // }
    if (NRF_GPIOTE->EVENTS_IN[0] == 1){
      printf("Interrupted!");
      NVIC_DisableIRQ(GPIOTE_IRQn);
      NRF_GPIOTE->EVENTS_IN[0] = 0; 

      software_interrupt_init(SWI1_EGU1_IRQn);
      software_interrupt_trigger(SWI1_EGU1_IRQn);
      printf("Software Interrupt!");
      for (int i = 0; i < 1000; ++i){
	      nrf_delay_ms(i);
      }

    }


    nrf_delay_ms(100);
  }
}

