#include "LedComponent.hpp"

LedComponent::LedComponent(byte pin, byte pin_clock, uint8_t led_number)
    : _pin(pin), _pinClock(pin_clock), _ledNumber(led_number), _led(nullptr)
{}

LedComponent::~LedComponent()
{
    delete _led;
}

void LedComponent::setup()
{
    _led = new ChainableLED(_pinClock,_pin,_ledNumber);
}

void LedComponent::setColor(uint8_t led_number, Color color)
{
    if(led_number >= _ledNumber)
        return;
    _led->setColorRGB(led_number,color.red,color.green,color.blue);
}