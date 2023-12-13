#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "ServerHandler.hpp"
#include "Component.hpp"
#include "Screen.hpp"

#ifdef SSID_CLOVER
    const char* ssid = SSID_CLOVER;
#endif
#ifdef PSWD_CLOVER
    const char* pswd = PSWD_CLOVER;
#endif

Component humidity(ComponentType::Analog, PIN_A0);

void setup()
{
    Serial.begin(9600);
    Display::Screen::GetInstance().Setup(const_cast<uint8_t*>(u8g2_font_busdisplay8x5_tr));
    ServerHandler::GetInstance().setup(ssid, pswd);
}

void loop()
{
    // Creating variables to access singletons
    auto& serverHandler = ServerHandler::GetInstance();
    auto& dataHandler = DataHandler::GetInstance();
    auto& screen = Display::Screen::GetInstance();

    // Could not connect after setup: Showing screen failure
    if(!serverHandler.isConnected())
    {
        screen.notConnected();
        return;
    }

    // Server showing IP
    if(!serverHandler.showBoot())
    {
        serverHandler.showIp();
        delay(250);
        return;
    }

    // When Screen can boot (isBooting) and Server finished showing IP (showBoot)
    if(screen.isBooting() && serverHandler.showBoot())
    {
        screen.boot();
        delay(100);
        return;
    }

    // Data gathered from various sensors
    // 0 -> air(0), 0-300 -> dry(20), 300-700 -> humid (580), 700-950 -> water(940)
    auto humidityData = static_cast<float>(std::any_cast<int>(humidity.getValue()));
    auto temperatureData = random(300, 150) / 10.0;

    // Updating the data handler
    dataHandler.updateTemperatureData(temperatureData);
    dataHandler.updateHumidityData(humidityData);
    // (debug) Printing to serial the data
    Serial.println(dataHandler.getJsonData());
    // Screen showing
    screen.loop();
    // Server sending data
    serverHandler.loop();
}