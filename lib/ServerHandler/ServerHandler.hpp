#ifndef SERVERHANDLER_HPP
#define SERVERHANDLER_HPP

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "DataHandler.hpp"

class ServerHandler {
public:
    ServerHandler(DataHandler * dataHandler);
    void setup(const char* ssid, const char* password); 
    void loop();

private:
    ESP8266WebServer server;
    void handleRoot();
    DataHandler * dataHandler; // Pointeur vers dataHandler
};

#endif
