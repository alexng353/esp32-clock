#ifndef NTP_HPP
#define NTP_HPP

#include <ctime> // For time_t and struct tm

// Function to initialize the SNTP service
void initialize_sntp(void);

// Function to obtain the time from an NTP server
void obtain_time(void);

// Function to display the current time
void display_time(void);

#endif // NTP_HPP
