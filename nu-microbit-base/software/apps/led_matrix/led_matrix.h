#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "microbit_v2.h"

// Initialize the LED matrix display
void led_matrix_init(void);
void draw_string(char[], bool);

