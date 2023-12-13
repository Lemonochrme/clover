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
    void updatePlantHumidityData(float humidity);
    void updateAirTemperatureData(float temperature);
    void updateAirHumidityData(float humidity);
    void updateLightData(float light);
        
private:
    // Singleton
    DataHandler();
    ~DataHandler();
    DataHandler(const DataHandler&) = delete;
    DataHandler& operator=(const DataHandler&) = delete;

    // Variables
    float plantHumidity;
    float airTemperature;
    float airHumidity;
    float light;

    // Fonctions
    String buildJson();
};

#endif