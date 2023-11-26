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
    Display::Screen::GetInstance().Setup(const_cast<uint8_t*>(u8g2_font_helvB08_tr));
    ServerHandler::GetInstance().setup(ssid, pswd);
}

void loop()
{
    auto& serverHandler = ServerHandler::GetInstance();
    auto& dataHandler = DataHandler::GetInstance();

    dataHandler.updateTemperatureData(random(1800, 2200) / 100.0);
    // 0 -> air(0), 0-300 -> dry(20), 300-700 -> humid (580), 700-950 -> water(940)
    dataHandler.updateHumidityData(static_cast<float>(std::any_cast<int>(humidity.getValue())));
    Serial.println(dataHandler.getJsonData());
    delay(1000);

    serverHandler.loop();
}