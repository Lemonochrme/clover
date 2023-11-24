#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "ServerHandler.hpp"
#include "DataHandler.hpp"
#include "Component.hpp"
#include "Display.hpp"

DataHandler dataHandler;
ServerHandler serverHandler(&dataHandler); // Référence à dataHandler
Component humidity(ComponentType::Analog, PIN_A0);
Display screen;

void setup()
{
    Serial.begin(9600);
    serverHandler.setup("Iphone de Nicole", "cesthonteux");
}

void loop()
{
    screen.loop();
    dataHandler.updateTemperatureData(random(1800, 2200) / 100.0);
    dataHandler.updateHumidityData(static_cast<float>(std::any_cast<int>(humidity.getValue())));
    Serial.println(dataHandler.getJsonData());
    delay(1000);

    serverHandler.loop();
}
