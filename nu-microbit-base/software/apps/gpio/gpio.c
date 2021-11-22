#include <stdio.h>
#include "gpio.h"

typedef struct{
  // Step 3:
  // Add register definitions here
  uint32_t OUT;
  uint32_t OUTSET;
  uint32_t OUTCLR;
  uint32_t IN;
  uint32_t DIR;
  uint32_t DIRSET;
  uint32_t DIRCLR;
  uint32_t LATCH;
  uint32_t DETECTMODE;
  uint32_t unused_[118];
  uint32_t PIN_CNF[32];
  
} gpio_reg_t;


volatile gpio_reg_t* PORT_0 = (gpio_reg_t*)(0x50000504);
volatile gpio_reg_t* PORT_1 = (gpio_reg_t*)(0x50000804);

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
//  dir - gpio direction (INPUT, OUTPUT)
void gpio_config(uint8_t gpio_num, gpio_direction_t dir) {
  // Implement me
  // Hint: Use proper PIN_CNF instead of DIR
  PORT_0->PIN_CNF[gpio_num] = dir;
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_set(uint8_t gpio_num) {
  // Implement me

  uint32_t bits = 1 << gpio_num;
  
  PORT_0->OUTSET = PORT_0->OUTSET | bits; 
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_clear(uint8_t gpio_num) {
  // Implement me
  
  uint32_t bits = 1 << gpio_num;
 
  PORT_0->OUTCLR = PORT_0->OUTCLR | bits;

}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
// Output:
//  bool - pin state (true == high)
bool gpio_read(uint8_t gpio_num) {
  // Implement me

  return (PORT_0->IN >> gpio_num) & 1;
}

void gpio_print() {

  printf("%p", &(PORT_0->LATCH));

}
