#include "ServerHandler.hpp"
#include "../Display/Screen.hpp"

ServerHandler::ServerHandler() : server(80), display_time(0) {
}

ServerHandler::~ServerHandler() {}

void ServerHandler::setup(const char* ssid, const char* password) { // On utilise les scope resolution operator pour définir les méthodes la classe ServerHandle qui elle est dans hpp
    uint8_t state(0);
    Serial.begin(9600);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Display::Screen::GetInstance().connecting(state);
        state >= 3 ? state = 0: state++;
    }

    server.begin();
    server.on("/", [this]() { this->handleRoot(); }); // fonction lamda pour gérer les requettes get
}

void ServerHandler::loop() {
    if(display_time < MAX_TIME)
    {
        Display::Screen::GetInstance().connected(WiFi.localIP().toString().c_str(),display_time);
        display_time++;
    }
    server.handleClient();
}

bool ServerHandler::showNext()
{
    return (display_time >= MAX_TIME);
}

void ServerHandler::handleRoot() {
    auto& dataHandler = DataHandler::GetInstance();
    String jsonFormattedData = dataHandler.getJsonData();
    server.send(200, "application/json", jsonFormattedData);
}
