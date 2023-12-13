#ifndef SERVERHANDLER_HPP
#define SERVERHANDLER_HPP

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "DataHandler.hpp"

constexpr uint8_t MAX_TIME = 28;
constexpr uint16_t MAX_CONNECT_TRIES = 20;

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
    void showIp();
    void loop();
    bool isConnected();
    bool showBoot();

private:
    // Singleton
    ServerHandler();
    ~ServerHandler();
    ServerHandler(const ServerHandler&) = delete;
    ServerHandler& operator=(const ServerHandler&) = delete;
    // Private variables/functions
    void handleRoot();
    ESP8266WebServer server;
    uint8_t display_time;
    bool _connected;
};

#endif
