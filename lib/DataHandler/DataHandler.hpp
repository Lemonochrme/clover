#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include <ArduinoJson.h>

class DataHandler {
public:
    DataHandler();
    String getJsonData();

    void updateTemperatureData(float temperature);
    void updateHumidityData(float humidity);
        
private:
    float temperature;
    float humidity;

    String buildJson();
};

#endif