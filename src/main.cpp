#include <Arduino.h>
#include "WebServer.h"
#include "WateringZone.h"
#include "WiFiManager.h"

// Define your watering zones
std::vector<WateringZone> wateringZones;

void setupWateringZones() {
    // Dynamically add watering zones to the vector
    wateringZones.push_back(WateringZone(3, 10000)); // Zone 1: Pin 23, 10 seconds
    wateringZones.push_back(WateringZone(4, 15000)); // Zone 2: Pin 24, 15 seconds
    wateringZones.push_back(WateringZone(5, 12000)); // Zone 3: Pin 25, 12 seconds
    wateringZones.push_back(WateringZone(6, 8000));  // Zone 4: Pin 26, 8 seconds

    // Initialize each zone
    for (auto& zone : wateringZones) {
        zone.setup();
    }
}

MyWebServer webServer; // Create an instance of MyWebServer

void setup() {
    Serial.begin(115200); // Start the Serial communication at 115200 baud rate

    // Initialize watering zones
    Serial.println("Setting up watering zones...");
    setupWateringZones();

    // Set up the web server
    Serial.println("Setting up web server...");
    webServer.setup(); // Initialize the web server and Wi-Fi connection
}

void loop() {
    static unsigned long lastPrintTime = 0; // Keep track of time between checks

    if (millis() - lastPrintTime > 2000) {  // Check every 2 seconds
        checkConnectedDevices();
        lastPrintTime = millis();
    }
}

