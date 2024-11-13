#ifndef WATERING_ZONE_H
#define WATERING_ZONE_H

class WateringZone {
public:
    WateringZone(int pin, int duration);  // Constructor to set up the zone
    void setup();                          // Initialize the GPIO pin
    void water();                         // Activate the solenoid valve
    void update();                        // Update method to manage watering duration
    bool isActive();                      // Check if the zone is currently active
    void stopWatering();                  // Stop watering the zone

private:
    int pin;                              // GPIO pin number for the solenoid valve
    int duration;                         // Watering duration in milliseconds
    bool active;                          // Flag to indicate if watering is in progress
    unsigned long startTime;              // Variable to store the start time of watering
};

#endif
