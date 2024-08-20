#ifndef PWM_H
#define PWM_H

#include <stdint.h>  // For uint8_t and uint32_t types

// Function to mimic Arduino's analogWrite using ESP-IDF
void analogWrite(uint8_t pin, uint32_t value, uint32_t valueMax = 255);

#endif // PWM_H
