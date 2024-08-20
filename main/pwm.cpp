#include "driver/ledc.h"
#include "esp_err.h"

void analogWrite(uint8_t pin, uint32_t value, uint32_t valueMax = 255) {
  // Configure the LEDC timer
  ledc_timer_config_t ledc_timer = {
      .speed_mode = LEDC_LOW_SPEED_MODE,   // LEDC low-speed mode
      .duty_resolution = LEDC_TIMER_8_BIT, // Resolution of PWM duty
      .timer_num = LEDC_TIMER_0,           // Timer index
      .freq_hz = 5000,                     // Frequency of PWM signal
      .clk_cfg = LEDC_AUTO_CLK,            // Auto select the source clock
  };
  ledc_timer_config(&ledc_timer);

  // Configure the LEDC channel
  ledc_channel_config_t ledc_channel = {
      .gpio_num = pin,
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = LEDC_CHANNEL_0,
      .timer_sel = LEDC_TIMER_0,
      .duty = 0,
      .hpoint = 0,
  };
  ledc_channel_config(&ledc_channel);

  // Calculate the duty cycle
  uint32_t duty = (value * 255) / valueMax;

  // Set the duty cycle for the channel
  ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, duty);
  ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
}
