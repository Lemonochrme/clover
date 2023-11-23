#ifndef SERVERHANDLER_HPP
#define SERVERHANDLER_HPP

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

class ServerHandler {
public:
    ServerHandler(); 
    void setup(const char* ssid, const char* password); 
    void loop();

private:
    ESP8266WebServer server;
    int readSensorData();
    void sendDataToServer(char * data);
    void handleRoot();
};

#endif
