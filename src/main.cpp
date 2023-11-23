#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "ServerHandler.hpp"
#include "DataHandler.hpp"

ServerHandler serverHandler;
DataHandler dataHandler;

int cpt = 0;

void setup() {
    Serial.begin(9600);

    dataHandler.updateTemperatureData(20.0);
    dataHandler.updateHumidityData(3.141592);

    serverHandler.setup("Redmi Note 10", "bbooksdd");
}

void loop() {
    serverHandler.loop();

    Serial.println(dataHandler.getJsonData());
    dataHandler.updateTemperatureData(cpt++);
    delay(1000);
}
