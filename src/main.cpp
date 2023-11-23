#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "ServerHandler.hpp"
#include "DataHandler.hpp"

DataHandler dataHandler;
ServerHandler serverHandler(&dataHandler); // Référence à dataHandler


void setup() {
    Serial.begin(9600);

    dataHandler.updateTemperatureData(20.0);
    dataHandler.updateHumidityData(3.141592);

    serverHandler.setup("Redmi Note 10", "bbooksdd");
}

void loop() {
    Serial.println(dataHandler.getJsonData());
    
    dataHandler.updateTemperatureData(random(1800, 2200)/100.0);
    dataHandler.updateHumidityData(random(4400, 5000)/100.0);
    delay(1000);


    serverHandler.loop();
}
