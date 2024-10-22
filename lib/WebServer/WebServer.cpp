#include "WebServer.h"
#include "WiFiManager.h"
#include "config.h"

// Declare the watering zones as external
extern std::vector<WateringZone> wateringZones;


// Constructor to set up the Web Server
MyWebServer::MyWebServer() : server(80) {   // Initialize the AsyncWebServer on port 80
}

// Initialize the Web Server
void MyWebServer::setup() {
    // Call the WiFi setup from WiFiManager
    setupAP();
    Serial.println("Connected to Access Point!");

    // Set up the server routes
    setupRoutes();

    // Start the web server
    server.begin();
    Serial.println("Web server started!");
}

// Set up the HTTP routes
void MyWebServer::setupRoutes() {
    // Serve a simple HTML page for controlling watering zones
    server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
        String html = "<html><body>";
        html += "<h1>Watering Control</h1>";
        html += "<form action='/water' method='POST'>";
        html += "<label for='zone'>Select Zone:</label>";
        html += "<select name='zone' id='zone'>";
        for (int i = 0; i < wateringZones.size(); i++) {
            html += "<option value='" + String(i) + "'>Zone " + String(i + 1) + "</option>";
        }
        html += "</select>";
        html += "<input type='submit' value='Water Zone'>";
        html += "</form>";
        html += "</body></html>";
        request->send(200, "text/html", html);
    });

    // Define a simple route for status
    server.on("/status", HTTP_GET, [this](AsyncWebServerRequest *request) {
        handleStatus();
        request->send(200, "text/plain", "System is running.");
    });

    // Define a route for handling watering zone requests
    server.on("/water", HTTP_POST, [this](AsyncWebServerRequest *request) {
        int zone = request->arg("zone").toInt(); // Get the zone number from the request
        if (zone >= 0 && zone < wateringZones.size()) {
            handleWaterZone(zone); // Call the handleWaterZone method for the specific zone
            request->send(200, "text/plain", "Watering zone action performed for Zone " + String(zone + 1) + ".");
        } else {
            request->send(400, "text/plain", "Invalid zone selected.");
        }
    });
}

// Handle status requests
void MyWebServer::handleStatus() {
    Serial.println("Handling status request...");
    // Return the status of the system (e.g., network status, uptime, etc.)
}

// Handle watering zone requests
void MyWebServer::handleWaterZone(int zone) {
    // Activate the specified watering zone
    wateringZones[zone].water();

    // Yield to the watchdog to prevent a timeout
    delay(0);  // This allows the watchdog to reset the device if needed
}
