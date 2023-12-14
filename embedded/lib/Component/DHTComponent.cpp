#include "DHTComponent.hpp"

DHTComponent::DHTComponent(uint8_t type, byte pin)
    : _pin(pin), _type(type), _dht(nullptr)
{}

DHTComponent::~DHTComponent()
{
    delete _dht;
}

void DHTComponent::setup()
{
    _dht = new DHT_Unified(_pin, _type);
    _dht->begin();
}

float DHTComponent::getHumidity()
{
    _dht->humidity().getEvent(&_event);
    return _event.relative_humidity;
}

float DHTComponent::getTemperature()
{
    _dht->temperature().getEvent(&_event);
    return _event.temperature;
}
