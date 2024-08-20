// stdlib
#include <cstring>
#include <stdio.h>

// from ESP-IDF
#include "driver/gpio.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/gpio_types.h"
#include "ntp.hpp"
#include "nvs_flash.h"

// my libraries
#include "consts.hpp"
#include "ntp.hpp"
#include "pwm.hpp"
#include "setup.hpp"
#include "wifi.hpp"

#define BLINK GPIO_NUM_32
#define DEFAULT_SSID "default"
#define DEFAULT_PASS "thispasswordissecure"
#define DEFAULT_SCAN_LIST_SIZE 10

void sleep(int ms) { vTaskDelay(ms / portTICK_PERIOD_MS); }

void set_hours(int hour) {
  gpio_set_level(H_ONES, hour % 2);
  gpio_set_level(H_TWOS, (hour / 2) % 2);
  gpio_set_level(H_FOURS, (hour / 4) % 2);
  gpio_set_level(H_EIGHTS, (hour / 8) % 2);
  gpio_set_level(H_SIXTEENS, (hour / 16) % 2);
}

void set_timezone(const char *tz) {
  setenv("TZ", tz, 1);
  tzset();
}

extern "C" void app_main(void) {
  int err = setup_gpio();
  if (err != 0) {
    return;
  }
  ESP_ERROR_CHECK(nvs_flash_init());

  wifi_init(DEFAULT_SSID, DEFAULT_PASS);
  wifi_scan();

  initialize_sntp();
  obtain_time();
  set_timezone("PST8PDT,M3.2.0/2,M11.1.0/2");

  gpio_set_direction(BLINK, GPIO_MODE_OUTPUT);

  for (;;) {
    for (int i = 0; i < 24; i++) {
      gpio_set_level(BLINK, i % 2);
      set_hours(i);
      display_time();
      sleep(1000);
    }
  }
}
