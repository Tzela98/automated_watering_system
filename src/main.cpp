#include <Arduino.h>
#include <vector>
#include "WebServer.h"
#include "WateringZone.h"
#include "WiFiManager.h"
#include "Globals.h" 

// Define your watering zones
std::vector<WateringZone> wateringZones;

void setupWateringZones() {
    // Dynamically add watering zones to the vector
    wateringZones.push_back(WateringZone(23, 10000)); 
    wateringZones.push_back(WateringZone(22, 15000)); 
    wateringZones.push_back(WateringZone(21, 12000)); 
    wateringZones.push_back(WateringZone(19, 8000));  

    // Initialize each zone
    for (size_t i = 0; i < wateringZones.size(); ++i) {
        Serial.print("Setting up watering zone ");
        Serial.println(i + 1);
        wateringZones[i].setup();
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

    // Update each watering zone and yield control to prevent blocking
    for (auto& zone : wateringZones) {
        zone.update();
        yield();  // Allows background tasks to run
    }
}

