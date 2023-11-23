#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "ServerHandler.hpp"

ServerHandler serverHandler;

void setup() {
    serverHandler.setup("Redmi Note 10", "bbooksdd");
}

void loop() {
    serverHandler.loop();
}
