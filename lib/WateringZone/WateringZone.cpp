#include <Arduino.h>
#include "WateringZone.h"

// Constructor to set up the zone
WateringZone::WateringZone(int pin, int duration) 
    : pin(pin), duration(duration), active(false), startTime(0) {}

// Initialize the GPIO pin
void WateringZone::setup() {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    Serial.println("Watering zone setup complete!");
}

// Start watering the zone
void WateringZone::water() {
    if (!active) {
        Serial.print("Watering zone ");
        Serial.println(pin);

        digitalWrite(pin, HIGH);  // Turn on the solenoid valve
        active = true;            // Set the active flag
        startTime = millis();     // Record the start time
    }
}

// Update method to manage watering duration
void WateringZone::update() {
    if (active) {
        // Check if the duration has elapsed
        if (millis() - startTime >= duration) {
            stopWatering(); // Stop watering when the duration is over
        }
    }
}

// Check if the zone is currently active
bool WateringZone::isActive() {
    return active;
}

// Stop watering the zone
void WateringZone::stopWatering() {
    if (active) {
        Serial.print("Stopping watering for zone ");
        Serial.println(pin);

        digitalWrite(pin, LOW);  // Turn off the solenoid valve
        active = false;          // Clear the active flag

        Serial.println("Watering stopped.");
    }
}
