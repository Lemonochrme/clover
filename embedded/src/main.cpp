#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "ServerHandler.hpp"
#include "Component.hpp"
#include "LedComponent.hpp"
#include "DHTComponent.hpp"
#include "Screen.hpp"

#ifdef SSID_CLOVER
    const char* ssid = SSID_CLOVER;
#endif
#ifdef PSWD_CLOVER
    const char* pswd = PSWD_CLOVER;
#endif

Component humidity(ComponentType::Analog, PIN_A0);
LedComponent led(D8,D7,2);
DHTComponent airSensor(DHT11,D3);

void setup()
{
    // Sensors/Acuators setup
    led.setup();
    airSensor.setup();
    // Lights are off when powered
    led.setColor(0,{0,0,0});
    led.setColor(1,{0,0,0});

    // Setup for screen and server
    Serial.begin(9600);
    Display::Screen::GetInstance().Setup(const_cast<uint8_t*>(u8g2_font_busdisplay8x5_tr));
    ServerHandler::GetInstance().setup(ssid, pswd);
    // Printing server data
    Serial.print("Connected to WiFi. IP address: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
    // Creating variables to access singletons
    auto& serverHandler = ServerHandler::GetInstance();
    auto& dataHandler = DataHandler::GetInstance();
    auto& screen = Display::Screen::GetInstance();
    led.setColor(0,{32,0,0});
    led.setColor(1,{0,32,0});

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
    auto soilHumidityData = static_cast<float>(std::any_cast<int>(humidity.getValue()));
    auto airTemperatureData = airSensor.getTemperature();
    auto airHumidityData = airSensor.getHumidity();

    // Updating the data handler
    dataHandler.updateSoilMoistureData(soilHumidityData);
    dataHandler.updateAirTemperatureData(airTemperatureData);
    dataHandler.updateAirHumidityData(airHumidityData);

    // Screen showing
    screen.loop((soilHumidityData/950.0f)*100.0f,airTemperatureData,airHumidityData);
    
    // TODO: Add LedComponent management
    if (soilHumidityData < 550) {
        Serial.println("Soil humidity low. Please water the plant.");
    } else if (soilHumidityData >= 550 && soilHumidityData <= 680) {
        Serial.println("Idle...");
    } else {
        Serial.println("Soil too wet.");
        Serial.println("Soil too wet.");
    }

    serverHandler.loop();
}