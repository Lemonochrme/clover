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

    /**
     * @brief setup the wifi when the Arduino is starting its connections
     * 
     * @param ssid the name of the wifi
     * @param password the password of the wifi
     */
    void setup(const char* ssid, const char* password); 

    /**
     * @brief Calls the Screen Singleton and shows the IP during a certain time.
     */
    void showIp();

    /**
     * @brief The basic loop of the Server, sending JSON data over the port 80.
     */
    void loop();

    /**
     * @return true if connected to the wifi
     * @return false if failed to connect
     */
    bool isConnected();

    /**
     * @return true When finished showing IP and connecting
     * @return false still in state of connecting
     */
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
