#include <Arduino.h>
#include "WateringZone.h"
#include <time.h>

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

// Add a watering schedule
void WateringZone::addSchedule(const WateringSchedule &schedule) {
    schedules.push_back(schedule);
    Serial.println("Watering schedule added.");
}

// Clear the watering schedule
void WateringZone::clearSchedule() {
    schedules.clear();
    Serial.println("Watering schedule cleared.");
}

// Check the watering schedule
unsigned long lastTriggerTime = 0;

void WateringZone::checkSchedule() {
    time_t now = time(nullptr);
    struct tm *timeInfo = localtime(&now);

    for (const WateringSchedule &schedule : schedules) {
        if (schedule.days[timeInfo->tm_wday] &&
            timeInfo->tm_hour == schedule.startHour &&
            timeInfo->tm_min == schedule.startMinute) {

            if (lastTriggerTime != now) { // Avoid re-triggering
                Serial.println("Watering scheduled time reached.");
                water();
                duration = schedule.duration;
                lastTriggerTime = now;
            }
        }
    }
}
