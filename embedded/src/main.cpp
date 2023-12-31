#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "ServerHandler.hpp"
#include "MainComponent.hpp"
#include "Screen.hpp"
#include "warning.hpp"

#ifdef SSID_CLOVER
const char *ssid = SSID_CLOVER;
#endif
#ifdef PSWD_CLOVER
const char *pswd = PSWD_CLOVER;
#endif

void setup()
{
    // Sensors/Acuators setup
    MainComponent::GetInstance().setup();

    // Setup for screen and server
    Serial.begin(9600);
    Display::Screen::GetInstance().Setup(const_cast<uint8_t *>(u8g2_font_busdisplay8x5_tr));
    ServerHandler::GetInstance().setup(ssid, pswd);

    // Printing server data
    Serial.print("Connected to WiFi. IP address: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
    // Creating variables to access singletons
    auto &serverHandler = ServerHandler::GetInstance();
    auto &dataHandler = DataHandler::GetInstance();
    auto &screen = Display::Screen::GetInstance();

    // Could not connect after setup: Showing screen failure
    if (!serverHandler.isConnected())
    {
        screen.notConnected();
        return;
    }

    // Server showing IP
    if (!serverHandler.showBoot())
    {
        serverHandler.showIp();
        delay(250);
        return;
    }

    // When Screen can boot (isBooting) and Server finished showing IP (showBoot)
    if (screen.isBooting() && serverHandler.showBoot())
    {
        screen.boot();
        delay(100);
        return;
    }

    // Data gathered from various sensors
    // 0 -> air(0), 0-300 -> dry(20), 300-700 -> humid (580), 700-950 -> water(940)
    auto soilHumidityData = static_cast<float>(std::any_cast<int>(MainComponent::GetInstance().getHumidity().getValue()));
    auto airTemperatureData = MainComponent::GetInstance().getDHT().getTemperature();
    auto airHumidityData = MainComponent::GetInstance().getDHT().getHumidity();

    // Updating the data handler
    dataHandler.updateSoilMoistureData(soilHumidityData);
    dataHandler.updateAirTemperatureData(airTemperatureData);
    dataHandler.updateAirHumidityData(airHumidityData);

    // Showing screen
    screen.loop((soilHumidityData / 950.0f) * 100.0f, airTemperatureData, airHumidityData);
    Warning::warningLedLoop(soilHumidityData);
    Warning::warningScreenLoop(soilHumidityData,airTemperatureData,airHumidityData);

    serverHandler.loop();
}