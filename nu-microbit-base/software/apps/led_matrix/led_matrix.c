// LED Matrix Driver
// Displays characters on the LED matrix

#include <stdbool.h>
#include <stdio.h>

#include "nrf_gpio.h"
#include "app_timer.h"

#include "led_matrix.h"
#include "font.h"
#include "microbit_v2.h"

// static void row1toggle(void){
//   nrf_gpio_pin_toggle(LED_ROW2);
//   nrf_gpio_pin_toggle(LED_COL1);
//   nrf_gpio_pin_toggle(LED_COL2);
//   nrf_gpio_pin_toggle(LED_COL3);
//   nrf_gpio_pin_toggle(LED_COL4);
//   nrf_gpio_pin_toggle(LED_COL5);
// }

bool leds[5][5] = {false};
int led_row = 0;

uint32_t ROWs[] = {LED_ROW1, LED_ROW2, LED_ROW3 , LED_ROW4, LED_ROW5};
uint32_t COLs[] = {LED_COL1, LED_COL2, LED_COL3 , LED_COL4, LED_COL5};

char display_string[32];
int dslen;
int ds;
bool dsloop;

void draw_letter(char x){
  uint8_t y; // 1 of 5 8-bit rows of the letter
  for(int i = 0; i < 5; ++i){
    y = font[(int)x][i];
    for(int j = 0; j < 5; ++j){
      leds[i][j] = y & 0x1;
      y = y >> 1;
    }
  }
}

void next_letter(void* _unused){
    draw_letter(display_string[ds]);
    ++ds;
    if(ds > dslen ){
      if(dsloop){
      	ds = 0;
      }else{
      	draw_letter(' ');
      }
    }
  }

void draw_string(char x[], bool again){
  strcpy(display_string, x);
  dslen = strlen(x);
  ds = 0;
  dsloop = again;
  
  APP_TIMER_DEF(stringtimer);
  app_timer_create(&stringtimer, APP_TIMER_MODE_REPEATED, next_letter);
  app_timer_start(stringtimer, 35768, NULL);
}

void draw_marquee(char x[], bool again){
  strcpy(display_string, x);
  dslen = strlen(x);
  ds = 0;
  dsloop = again;
  
  uint8_t y; // 1 of 5 8-bit rows of the leading letter
  uint8_t z; // 1 of 5 8-bit rows of the trailing letter
  
  for(int i = 0; i < dslen; ++i){
    
  }
  
  
  for(int i = 0; i < 5; ++i){
    y = font[(int)x][i];
    for(int j = 0; j < 5; ++j){
      leds[i][j] = y & 0x1;
      y = y >> 1;
    }
  }
}

static void draw(void* _unused){
  for (int r = 0; r < 5; ++r) {
    nrf_gpio_pin_clear(ROWs[r]);
  }

  for(int i = 0; i < 5; ++i){
    if(leds[led_row][i]) {
      nrf_gpio_pin_clear(COLs[i]);
    } else {
      nrf_gpio_pin_set(COLs[i]);
    }
  } 
  nrf_gpio_pin_set(ROWs[led_row]);
  ++led_row;

  if (led_row > 4) {
    led_row = 0;
  }
}

void led_matrix_init(void) {
  // default state for the LED display
  // for(int i = 0; i<5; ++i){
  //   leds[i][i] = true;
  // }
  // for (int i = 4; i >= 0; --i){
  //   leds[i][4 - i] = true;
  // }
  bool q[5][5] = {{1, 0, 0, 0, 1},
    {0, 1, 0, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 0, 1, 0},
    {1, 0, 0, 0, 1}};
  memcpy(leds, q, sizeof q);

  // initialize row pins
  nrf_gpio_pin_dir_set(LED_ROW1, NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_dir_set(LED_ROW2, NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_dir_set(LED_ROW3, NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_dir_set(LED_ROW4, NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_dir_set(LED_ROW5, NRF_GPIO_PIN_DIR_OUTPUT);

  // initialize col pins
  nrf_gpio_pin_dir_set(LED_COL1, NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_dir_set(LED_COL2, NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_dir_set(LED_COL3, NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_dir_set(LED_COL4, NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_dir_set(LED_COL5, NRF_GPIO_PIN_DIR_OUTPUT);

  // set default values for pins
  nrf_gpio_pin_set(LED_COL1);
  nrf_gpio_pin_set(LED_COL2);
  nrf_gpio_pin_set(LED_COL3);
  nrf_gpio_pin_set(LED_COL4);
  nrf_gpio_pin_set(LED_COL5);
  nrf_gpio_pin_clear(LED_ROW1);
  nrf_gpio_pin_clear(LED_ROW2);
  nrf_gpio_pin_clear(LED_ROW3);
  nrf_gpio_pin_clear(LED_ROW4);
  nrf_gpio_pin_clear(LED_ROW5);

  // initialize timer(s) (Part 3 and onwards)
  APP_TIMER_DEF(timer0);

  app_timer_init();
  app_timer_create(&timer0, APP_TIMER_MODE_REPEATED, draw);
  app_timer_start(timer0, 100, NULL);

  //draw_letter('%');

}
