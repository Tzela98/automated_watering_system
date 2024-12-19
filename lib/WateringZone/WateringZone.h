#ifndef WATERING_ZONE_H
#define WATERING_ZONE_H

#include <vector>

// Define a struct for the watering schedule
struct WateringSchedule {
    int startHour;     // Start time (hour in 24-hour format)
    int startMinute;   // Start time (minute)
    int duration;      // Duration in minutes
    bool days[7];      // Boolean array for days of the week (Sun=0, Mon=1, ...)
};

class WateringZone {
public:
    WateringZone(int pin, int duration);  // Constructor to set up the zone
    void setup();                          // Initialize the GPIO pin
    void water();                         // Activate the solenoid valve
    void update();                        // Update method to manage watering duration
    bool isActive();                      // Check if the zone is currently active
    void stopWatering();                  // Stop watering the zone
    void addSchedule(const WateringSchedule &schedule); // Add a watering schedule
    void clearSchedule();                 // Clear the watering schedule
    void checkSchedule();                 // Check the watering schedule

private:
    int pin;                              // GPIO pin number for the solenoid valve
    int duration;                         // Watering duration in milliseconds
    bool active;                          // Flag to indicate if watering is in progress
    unsigned long startTime;              // Variable to store the start time of watering
    std::vector<WateringSchedule> schedules; // Vector to store watering schedules
};

#endif
