#include "MainComponent.hpp"

MainComponent::MainComponent()
    : _humidity(ComponentType::Analog, PIN_A0), _led(D8, D7, 2), _dht(DHT11, D3)
{
}

MainComponent::~MainComponent()
{}

void MainComponent::setup()
{
    _led.setup();
    _dht.setup();
    // Lights are off when powered
    _led.setColor(0,{0,0,0});
    _led.setColor(1,{0,0,0});
}

Component& MainComponent::getHumidity() { return _humidity; }
LedComponent& MainComponent::getLed() { return _led; }
DHTComponent& MainComponent::getDHT() { return _dht; }
