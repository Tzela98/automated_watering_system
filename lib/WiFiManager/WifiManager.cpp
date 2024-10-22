#include <WiFi.h>
#include "../../include/config.h"
#include "WiFiManager.h"

void setupAP() {
    Serial.println("Creating access point...");
    
    // Start the Access Point
    if (WiFi.softAP(AP_SSID, AP_PASSWORD)) {
        Serial.println("Access Point started successfully!");
        Serial.print("AP IP address: ");
        Serial.println(WiFi.softAPIP()); // Print the AP's IP address
    } else {
        Serial.println("Failed to start Access Point.");
    }
}

void checkConnectedDevices() {
    // Get the number of connected devices
    int currentConnectedCount = WiFi.softAPgetStationNum(); 

    // Use a static variable to store the previous device count
    static int lastConnectedCount = -1; // Initialize with -1 so it prints on the first run

    // Check if the count has changed
    if (currentConnectedCount != lastConnectedCount) {
        Serial.print("Connected devices: ");
        Serial.println(currentConnectedCount);

        // Update the last connected count
        lastConnectedCount = currentConnectedCount;
    }
}
