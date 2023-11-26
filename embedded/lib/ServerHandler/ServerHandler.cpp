#include "ServerHandler.hpp"

ServerHandler::ServerHandler() : server(80) {
}

ServerHandler::~ServerHandler() {}

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
    server.on("/", [this]() { this->handleRoot(); }); // fonction lamda pour gérer les requettes get
}

void ServerHandler::loop() {
    server.handleClient();
}

void ServerHandler::handleRoot() {
    auto& dataHandler = DataHandler::GetInstance();
    String jsonFormattedData = dataHandler.getJsonData();
    server.send(200, "application/json", jsonFormattedData);
}
