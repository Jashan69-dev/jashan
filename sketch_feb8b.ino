#include <DHT.h>

#define DHTPIN 4    // DHT22 data pin connected to digital pin 2
#define DHTTYPE DHT22 // DHT 22 (AM2302)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    dht.begin();
}

void loop() {
    float temperature = dht.readTemperature();  // Read temperature (Celsius)
    float humidity = dht.readHumidity();        // Read humidity (%)

    if (!isnan(temperature) && !isnan(humidity)) {
        Serial.print(millis());  // Timestamp in milliseconds
        Serial.print(",");
        Serial.print(temperature);
        Serial.print(",");
        Serial.println(humidity);
    }
    
    delay(20000);  // Collect data every 10 seconds
}