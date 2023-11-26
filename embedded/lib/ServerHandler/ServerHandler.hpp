#ifndef SERVERHANDLER_HPP
#define SERVERHANDLER_HPP

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "DataHandler.hpp"

class ServerHandler {
public:
    // Singleton
    static ServerHandler& GetInstance()
    {
        static ServerHandler instance;
        return instance;
    }
    // Public functions
    void setup(const char* ssid, const char* password); 
    void loop();

private:
    // Singleton
    ServerHandler();
    ~ServerHandler();
    ServerHandler(const ServerHandler&) = delete;
    ServerHandler& operator=(const ServerHandler&) = delete;
    // Private variables/functions
    void handleRoot();
    ESP8266WebServer server;
};

#endif
