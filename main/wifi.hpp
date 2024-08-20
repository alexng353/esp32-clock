// wifi.h

#ifndef WIFI_HPP
#define WIFI_HPP

#include "esp_event.h"

// Constants
#define DEFAULT_SCAN_LIST_SIZE 10 // Maximum number of networks to scan for

// Function Prototypes

/**
 * @brief Event handler for Wi-Fi events and IP events.
 *
 * @param arg       User-defined argument
 * @param event_base  Event base ID
 * @param event_id    Event ID
 * @param event_data  Event data
 */
void wifi_event_handler(void *arg, esp_event_base_t event_base,
                        int32_t event_id, void *event_data);

/**
 * @brief Scans for available Wi-Fi networks and logs the SSIDs.
 */
void wifi_scan(void);

/**
 * @brief Initializes Wi-Fi, sets up the event handlers, and starts the Wi-Fi
 * connection.
 */
void wifi_init(const char *ssid, const char *pass);

#endif // WIFI_HPP
