#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include <ArduinoJson.h>

class DataHandler {
public:
    // Singleton
    static DataHandler& GetInstance()
    {
        static DataHandler instance;
        return instance;
    }

    // Public functions
    String getJsonData();
    void updateTemperatureData(float temperature);
    void updateHumidityData(float humidity);
    
private:
    // Singleton
    DataHandler();
    ~DataHandler();
    DataHandler(const DataHandler&) = delete;
    DataHandler& operator=(const DataHandler&) = delete;
    float temperature;
    float humidity;
    String buildJson();
};

#endif