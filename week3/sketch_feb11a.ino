#include <Arduino_LSM6DS3.h>
#include <WiFiNINA.h>
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

// Wi-Fi Credentials
const char WIFI_SSID[] = "OnePlus Nord CE 2";
const char WIFI_PASS[] = "jashandeep1234";

// Cloud Variables
float x, y, z;

// IoT Cloud Connection Handler
WiFiConnectionHandler ArduinoIoTPreferredConnection(WIFI_SSID, WIFI_PASS);

void onAccelXChange() {}
void onAccelYChange() {}
void onAccelZChange() {}

void initProperties() {
    ArduinoCloud.addProperty(x, READ, 1, onAccelXChange);
    ArduinoCloud.addProperty(y, READ, 1, onAccelYChange);
    ArduinoCloud.addProperty(z, READ, 1, onAccelZChange);
}

void setup() {
    Serial.begin(9600);
    while (!Serial);

    // Check if Wi-Fi module is working
    if (WiFi.status() == WL_NO_MODULE) {
        Serial.println("Wi-Fi module not detected!");
        while (1);
    }

    // Connect to Wi-Fi
    Serial.print("Connecting to Wi-Fi");
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi!");

    // Force NTP Time Sync
    Serial.println("Forcing NTP sync...");
    IPAddress timeServer;
    WiFi.hostByName("time.google.com", timeServer);
    delay(2000);  // Wait for time sync

    // Initialize IMU sensor
    if (!IMU.begin()) {
        Serial.println("Failed to initialize IMU!");
        while (1);
    }

    // Sync Cloud Variables
    initProperties();
    ArduinoCloud.begin(ArduinoIoTPreferredConnection);
}

void loop() {
    ArduinoCloud.update();

    if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(x, y, z);
        Serial.print(" X: "); Serial.print(x);
        Serial.print(" Y: "); Serial.print(y);
        Serial.print(" Z: "); Serial.println(z);
    }
    delay(500);
}
