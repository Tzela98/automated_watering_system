#include <Arduino.h>
#include "WateringZone.h"

// Constructor to set up the zone
WateringZone::WateringZone(int pin, int duration) : pin(pin), duration(duration), active(false) {}

// Initialize the GPIO pin
void WateringZone::setup(){
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

// Activate the solenoid valve
void WateringZone::water(){
    if (!active){
        Serial.print("Watering zone ");
        Serial.println(pin);

        digitalWrite(pin, HIGH);    // Turn on the solenoid valve
        active = true;              // Set the active flag
        delay(duration);            // Wait for the watering duration
        stopWatering();             // Stop watering the zone
    }
}

// Check if the zone is currently active
bool WateringZone::isActive(){
    return active;
}

// Stop watering the zone
void WateringZone::stopWatering(){
    if (active){
        Serial.print("Stopping watering for zone ");
        Serial.println(pin);

        digitalWrite(pin, LOW);     // Turn off the solenoid valve
        active = false;             // Clear the active flag

        Serial.println("Watering stopped.");
    }
}