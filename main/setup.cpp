#include <stdio.h>
#include "driver/gpio.h"
#include "consts.hpp"

int setup_gpio() {
  int init = gpio_set_direction(H_ONES, GPIO_MODE_OUTPUT);
  if (init != ESP_OK) {
    printf("init: %d\n", init);
    return 1;
  }
  init = gpio_set_direction(H_TWOS, GPIO_MODE_OUTPUT);
  if (init != ESP_OK) {
    printf("init: %d\n", init);
    return 1;
  }
  init = gpio_set_direction(H_FOURS, GPIO_MODE_OUTPUT);
  if (init != ESP_OK) {
    printf("init: %d\n", init);
    return 1;
  }
  init = gpio_set_direction(H_EIGHTS, GPIO_MODE_OUTPUT);
  if (init != ESP_OK) {
    printf("init: %d\n", init);
    return 1;
  }
  init = gpio_set_direction(H_SIXTEENS, GPIO_MODE_OUTPUT);
  if (init != ESP_OK) {
    printf("init: %d\n", init);
    return 1;
  }
  return 0;
}
