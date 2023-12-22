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

    /**
     * @brief Get the Json Data object
     * 
     * @return String 
     */
    String getJsonData();

    /**
     * @brief Update the moisture of the internal Data Handler
     * 
     * @param humidity 
     */
    void updateSoilMoistureData(float humidity);

    /**
     * @brief Update the moisture of the internal Data Handler
     * 
     * @param temperature 
     */
    void updateAirTemperatureData(float temperature);

    /**
     * @brief Update the moisture of the internal Data Handler
     * 
     * @param humidity 
     */
    void updateAirHumidityData(float humidity);

    /**
     * @brief Update the moisture of the internal Data Handler
     * 
     * @param light 
     */
    void updateLightData(float light);
private:
    // Singleton
    DataHandler();
    ~DataHandler();
    DataHandler(const DataHandler&) = delete;
    DataHandler& operator=(const DataHandler&) = delete;

    // Variables
    float soilMoisture;
    float airTemperature;
    float airHumidity;
    float light;

    // Fonctions
    String buildJson();
};

#endif