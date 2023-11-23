#include "DataHandler.hpp"

DataHandler::DataHandler() {}

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
    document["temperature"] = temperature;
    document["humidity"] = humidity;

    String jsonFormattedData;
    serializeJson(document, jsonFormattedData);
    return jsonFormattedData;
}