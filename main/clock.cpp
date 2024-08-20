#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

#include "pwm.hpp"

#define BLINK GPIO_NUM_0
#define HIGH 1
#define LOW 0

#define H_ONES GPIO_NUM_17
#define H_TWOS GPIO_NUM_16
#define H_FOURS GPIO_NUM_4
#define H_EIGHTS GPIO_NUM_0
#define H_SIXTEENS GPIO_NUM_2

void sleep(int ms) { vTaskDelay(ms / portTICK_PERIOD_MS); }

int setup() {
  esp_err_t init = gpio_set_direction(BLINK, GPIO_MODE_OUTPUT);
  if (init != ESP_OK) {
    printf("init: %d\n", init);
    return 1;
  }
  init = gpio_set_direction(H_ONES, GPIO_MODE_OUTPUT);
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

void set_hours(int hour) {
  gpio_set_level(H_ONES, hour % 2);
  gpio_set_level(H_TWOS, (hour / 2) % 2);
  gpio_set_level(H_FOURS, (hour / 4) % 2);
  gpio_set_level(H_EIGHTS, (hour / 8) % 2);
  gpio_set_level(H_SIXTEENS, (hour / 16) % 2);
}

extern "C" void app_main(void) {
  int init = setup();
  if (init != 0) {
    return;
  }

  for (;;) {
    for (int i = 0; i < 24; i++) {
      set_hours(i);
      sleep(1000);
    }
  }
}
