#include "WebServer.h"
#include "WiFiManager.h"
#include "SPIFFS.h"  
#include "../../include/config.h"
#include "../../include/globals.h"


MyWebServer::MyWebServer() : server(80) {}

// Initialize the Web Server and SPIFFS
void MyWebServer::setup() {
    Serial.println("Starting setup...");
    
    Serial.println("Starting SPIFFS...");
    if (!SPIFFS.begin()) {
        Serial.println("Failed to mount SPIFFS");
        return;
    }
    Serial.println("SPIFFS mounted successfully.");

    Serial.println("Setting up AP...");
    setupAP();
    Serial.println("Wi-Fi setup complete.");

    Serial.println("Setting up routes...");
    setupRoutes();
    Serial.println("Routes setup complete.");

    Serial.println("Starting server...");
    server.begin();
    Serial.println("Web server setup complete!");
}


// Set up HTTP routes
void MyWebServer::setupRoutes() {
    // Serve the external HTML file
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", "text/html");
    });

    // Serve the external CSS file
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/style.css", "text/css");
    });

    // Serve the external JavaScript file
    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/script.js", "application/javascript");
    });

    // Define a route for status
    server.on("/status", HTTP_GET, [this](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "System is running."); // Or provide dynamic status
    });

    // Handle watering zone requests
    server.on("/water", HTTP_POST, [this](AsyncWebServerRequest *request) {
        int zone = request->arg("zone").toInt();
        if (zone >= 0 && zone < wateringZones.size()) {
            handleWaterZone(zone);
            request->send(200, "text/plain", "Watering zone action performed for Zone " + String(zone + 1) + ".");
        } else {
            request->send(400, "text/plain", "Invalid zone selected.");
        }
    });

    // Define a route to get the list of available zones
    server.on("/zones", HTTP_GET, [this](AsyncWebServerRequest *request) {
        String zonesJson = "[";

        // Assuming wateringZones is a vector or list that holds zone objects
        for (int i = 0; i < wateringZones.size(); i++) {
            zonesJson += String(i + 1); // Zone numbers, starting from 1
            if (i < wateringZones.size() - 1) {
                zonesJson += ","; // Add a comma between zones
            }
        }

        zonesJson += "]";
        request->send(200, "application/json", zonesJson); // Send the zones as JSON
    });
}

void MyWebServer::handleWaterZone(int zone) {
    // Activate the watering zone
    wateringZones[zone].water();
}
