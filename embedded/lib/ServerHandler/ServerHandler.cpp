#include "ServerHandler.hpp"

#include "MainComponent.hpp"
#include "../Display/Screen.hpp"

inline void led_blink(LedComponent& led)
{
    led.setColor(0,LedColors::WIFI_ON);
    delay(50);
    led.setColor(0,LedColors::LED_OFF);
}

ServerHandler::ServerHandler() : server(80), display_time(0), _connected(false)
{
}

ServerHandler::~ServerHandler() {}

void ServerHandler::setup(const char *ssid, const char *password)
{ // On utilise les scope resolution operator pour définir les méthodes la classe ServerHandle qui elle est dans hpp
    uint8_t state(0);
    uint16_t tryConnection(0);
    auto& led = MainComponent::GetInstance().getLed();
    Serial.begin(9600);
    WiFi.begin(ssid, password);

    // Testing connection
    while ((WiFi.status() != WL_CONNECTED) && (tryConnection < MAX_CONNECT_TRIES))
    {
        led_blink(led);
        delay(50);
        led_blink(led);
        delay(350);
        Display::Screen::GetInstance().connecting(state);
        state >= 3 ? state = 0 : state++;
        tryConnection++;
    }

    if (tryConnection < MAX_CONNECT_TRIES)
    {
        _connected = true;
        auto color = LedColors::WIFI_ON;
        led.setColor(0,color-15,200);
        server.begin();
        server.on("/", [this]()
                { this->handleRoot(); }); // fonction lamda pour gérer les requettes get
    }
    else {
        led.setColor(0,LedColors::NO_WIFI,200);
    }
}

void ServerHandler::loop()
{
    server.handleClient();
}

void ServerHandler::showIp()
{
    Display::Screen::GetInstance().connected(WiFi.localIP().toString().c_str(), display_time);
    display_time++;
}

bool ServerHandler::isConnected() { return _connected; }
bool ServerHandler::showBoot() { return (display_time >= MAX_TIME); }

void ServerHandler::handleRoot()
{
    auto &dataHandler = DataHandler::GetInstance();
    String jsonFormattedData = dataHandler.getJsonData();
    server.send(200, "application/json", jsonFormattedData);
}