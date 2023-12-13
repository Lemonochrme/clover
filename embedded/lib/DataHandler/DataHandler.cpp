#include "DataHandler.hpp"

DataHandler::DataHandler() {}

DataHandler::~DataHandler() {}

void DataHandler::updateTemperatureData(float temp) {
    temperature = temp;
}

void DataHandler::updateHumidityData(float hum) {
    humidity = hum;
}

String DataHandler::getJsonData() {
    return buildJson();
}

String DataHandler::buildJson() {
    StaticJsonDocument<200> document; // Taille = 200

    String MoistureSensorStatus;
    if (humidity > 10) {
        MoistureSensorStatus = "active";
    } else {
        MoistureSensorStatus = "inactive";
    }

    String soilMoistureLevel;
    if (humidity < 550) {
        soilMoistureLevel = "dry";
    } else if (humidity >= 550 && humidity <= 680) {
        soilMoistureLevel = "moist";
    } else {
        soilMoistureLevel = "wet";
    }

    document["device"]["device_id"] = "clv_0001";
    document["device"]["moisture_sensor_status"] = MoistureSensorStatus;
    document["raw_sensor_data"]["temperature"] = temperature;
    document["raw_sensor_data"]["soil_humidity"] = humidity;
    document["plant_management"]["soil_moisture"] = soilMoistureLevel;

    String jsonFormattedData;
    serializeJson(document, jsonFormattedData);
    return jsonFormattedData;
}