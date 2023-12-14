#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "ServerHandler.hpp"
#include "Component.hpp"
#include "LedComponent.hpp"
#include "Screen.hpp"

#ifdef SSID_CLOVER
    const char* ssid = SSID_CLOVER;
#endif
#ifdef PSWD_CLOVER
    const char* pswd = PSWD_CLOVER;
#endif

Component humidity(ComponentType::Analog, PIN_A0);
LedComponent led(D8,D7,2);

void setup()
{
    Serial.begin(9600);
    Display::Screen::GetInstance().Setup(const_cast<uint8_t*>(u8g2_font_busdisplay8x5_tr));
    ServerHandler::GetInstance().setup(ssid, pswd);

    Serial.print("Connected to WiFi. IP address: ");
    Serial.println(WiFi.localIP());

    pinMode(D5, OUTPUT);
    digitalWrite(D5, LOW);
    led.setup();
}

void loop()
{
    // Creating variables to access singletons
    auto& serverHandler = ServerHandler::GetInstance();
    auto& dataHandler = DataHandler::GetInstance();
    auto& screen = Display::Screen::GetInstance();
    led.setColor(0,{255,0,0});
    led.setColor(1,{0,255,0});

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
    auto airTemperatureData = random(150, 300) / 10.0;
    auto airHumidityData = random(0, 1000) / 10.0;
    auto lightData = random(0, 1000) / 10.0;

    // Updating the data handler
    dataHandler.updateSoilMoistureData(soilHumidityData);
    dataHandler.updateAirTemperatureData(airTemperatureData);
    dataHandler.updateAirHumidityData(airHumidityData);
    dataHandler.updateLightData(lightData);

    // Screen showing
    screen.loop(soilHumidityData,airTemperatureData,airHumidityData,lightData);
    
    if (soilHumidityData < 550) {
        Serial.println("Soil humidity low. Please water the plant.");
        digitalWrite(D5, HIGH);
    } else if (soilHumidityData >= 550 && soilHumidityData <= 680) {
        Serial.println("Idle...");
        digitalWrite(D5, LOW);
    } else {
        Serial.println("Soil too wet.");
        digitalWrite(D5, LOW);
        delay(400);
        digitalWrite(D5, HIGH);
        delay(400);
    }

    serverHandler.loop();
}