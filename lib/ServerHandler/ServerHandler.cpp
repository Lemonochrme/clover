#include "ServerHandler.hpp"

ServerHandler::ServerHandler() : server(80) {
}

void ServerHandler::setup(const char* ssid, const char* password) { // On utilise les scope resolution operator pour définir les méthodes la classe ServerHandle qui elle est dans hpp
    Serial.begin(9600);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("Connected to Wi-Fi. IP address: ");
    Serial.println(WiFi.localIP());

    server.begin();
    server.on("/", [this]() { this->sendDataToServer("Hello World!"); }); // fonction lamda pour gérer les requettes get
}

void ServerHandler::loop() {
    server.handleClient();
}

int ServerHandler::readSensorData() {
    return 123;
}

void ServerHandler::sendDataToServer(char * data) {
    server.send(200, "text/plain", data);
}

void ServerHandler::handleRoot() {
    server.send(200, "text/plain", "Sensor Data: " + String(readSensorData()));
}
