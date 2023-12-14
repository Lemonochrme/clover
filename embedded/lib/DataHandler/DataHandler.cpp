#include "DataHandler.hpp"

DataHandler::DataHandler() {}

DataHandler::~DataHandler() {}

void DataHandler::updateSoilMoistureData(float humidity) { soilMoisture = humidity; }
void DataHandler::updateAirTemperatureData(float temperature) { airTemperature = temperature; }
void DataHandler::updateAirHumidityData(float humidity) { airHumidity = humidity; }
void DataHandler::updateLightData(float light) { this->light = light; }

String DataHandler::getJsonData() {
    return buildJson();
}

String DataHandler::buildJson() {
    StaticJsonDocument<200> document; // Taille = 200

    String MoistureSensorStatus;
    if (soilMoisture > 10) {
        MoistureSensorStatus = "active";
    } else {
        MoistureSensorStatus = "inactive";
    }

    String soilMoistureLevel;
    if (soilMoisture < 550) {
        soilMoistureLevel = "dry";
    } else if (soilMoisture >= 550 && soilMoisture <= 680) {
        soilMoistureLevel = "moist";
    } else {
        soilMoistureLevel = "wet";
    }

    document["device"]["device_id"] = "clv_0001";
    document["device"]["moisture_sensor_status"] = MoistureSensorStatus;
    document["plant_management"]["soil_moisture"] = soilMoistureLevel;
    document["raw_sensor_data"]["airTemperature"] = airTemperature;
    document["raw_sensor_data"]["airHumidity"] = airHumidity;
    document["raw_sensor_data"]["light"] = light;

    String jsonFormattedData;
    serializeJson(document, jsonFormattedData);
    return jsonFormattedData;
}