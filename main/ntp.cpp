#include "esp_log.h"
#include "esp_sntp.h"
#include "freertos/task.h"
#include <ctime>

void initialize_sntp(void) {
  // Stop SNTP client if it is already running
  if (esp_sntp_enabled()) {
    esp_sntp_stop();
  }

  // Now it's safe to set the operating mode
  ESP_LOGI("SNTP", "Initializing SNTP");
  esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
  esp_sntp_setservername(0, "pool.ntp.org"); // Use a preferred NTP server
  esp_sntp_init();
}

void obtain_time(void) {
  initialize_sntp();

  // Wait for time to be set
  time_t now = 0;
  struct tm timeinfo = {0};
  int retry = 0;
  const int retry_count = 10;

  while (timeinfo.tm_year < (2016 - 1900) && ++retry < retry_count) {
    ESP_LOGI("SNTP", "Waiting for system time to be set... (%d/%d)", retry,
             retry_count);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    time(&now);
    localtime_r(&now, &timeinfo);
  }

  if (retry < retry_count) {
    ESP_LOGI("SNTP", "Time synchronized successfully");
  } else {
    ESP_LOGE("SNTP", "Failed to synchronize time");
  }
}

void display_time(void) {
  time_t now;
  struct tm timeinfo;

  time(&now);
  localtime_r(&now, &timeinfo);

  char strftime_buf[64];
  strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
  ESP_LOGI("TIME", "The current date/time is: %s", strftime_buf);
}
