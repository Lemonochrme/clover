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

float SoilHumidity;
float Temperature;

void setup()
{
    Serial.begin(9600);
    Display::Screen::GetInstance().Setup(const_cast<uint8_t*>(u8g2_font_busdisplay8x5_tr));
    ServerHandler::GetInstance().setup(ssid, pswd);

    Serial.print("Connected to WiFi. IP address: ");
    Serial.println(WiFi.localIP());

    pinMode(D5, OUTPUT);
    digitalWrite(D5, LOW);
}

void loop()
{
    auto& serverHandler = ServerHandler::GetInstance();
    auto& dataHandler = DataHandler::GetInstance();
    auto& screen = Display::Screen::GetInstance();

    // If could not connect, show screen failure
    if(!serverHandler.isConnected())
    {
        screen.notConnected();
        return;
    }

    // If serverHandler finished showing ip.
    if (serverHandler.showNext()) {
        //screen.loop(); -> Cause des problèmes
    }

    SoilHumidity = static_cast<float>(std::any_cast<int>(humidity.getValue()));
    Temperature = random(1800, 2200) / 100.0;

    dataHandler.updateTemperatureData(Temperature);
    dataHandler.updateHumidityData(SoilHumidity);
    
    if (SoilHumidity < 550) {
        Serial.println("Soil humidity low. Please water the plant.");
        digitalWrite(D5, HIGH);
    } else if (SoilHumidity >= 550 && SoilHumidity <= 680) {
        Serial.println("Perfect soil moisture condition. Idle...");
        digitalWrite(D5, LOW);
    } else {
        Serial.println("Soil too wet.");
        digitalWrite(D5, LOW);
        delay(400);
        digitalWrite(D5, HIGH);
        delay(400);
    }



    // When showing IP, delay is faster.
    delay(serverHandler.showNext() ? 1000 : 250);
    serverHandler.loop();
}