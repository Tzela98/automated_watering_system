#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "WateringZone.h"

// Declare NUM_ZONES as extern
extern const int NUM_ZONES;

class MyWebServer{
    public:
        MyWebServer();          // Constructor to set up the Web Server
        void setup();           // Initialize the Web Server

    private:
        AsyncWebServer server;          // ESP32 Web Server Instance
        void setupRoutes();             // Set up the HTTP routes
        void handleWaterZone(int Zone); // Handle watering zone requests
        void handleStatus();            // Handle status requests
};

#endif