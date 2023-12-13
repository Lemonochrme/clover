#include "DataHandler.hpp"

DataHandler::DataHandler() {}

DataHandler::~DataHandler() {}

void DataHandler::updatePlantHumidityData(float humidity) { plantHumidity = humidity; }
void DataHandler::updateAirTemperatureData(float temperature) { airTemperature = temperature; }
void DataHandler::updateAirHumidityData(float humidity) { airHumidity = humidity; }
void DataHandler::updateLightData(float light) { this->light = light; }

String DataHandler::getJsonData() {
    return buildJson();
}

String DataHandler::buildJson() {
    StaticJsonDocument<200> document; // Taille = 200
    document["plantHumidity"] = plantHumidity;
    document["airTemperature"] = airTemperature;
    document["airHumidity"] = airHumidity;
    document["light"] = light;

    String jsonFormattedData;
    serializeJson(document, jsonFormattedData);
    return jsonFormattedData;
}