#include "LedComponent.hpp"

Color Color::operator-(byte value)
{
    byte nullbyte(0);
    return {(this->red - value) < 0 ? nullbyte : static_cast<byte>(this->red - value),
            (this->blue - value) < 0 ? nullbyte : static_cast<byte>(this->blue - value),
            (this->green - value) < 0 ? nullbyte : static_cast<byte>(this->green - value)};
}

LedComponent::LedComponent(byte pin, byte pin_clock, uint8_t led_number)
    : _pin(pin), _pinClock(pin_clock), _ledNumber(led_number), _led(nullptr)
{
}

LedComponent::~LedComponent()
{
    delete _led;
}

void LedComponent::setup()
{
    _led = new ChainableLED(_pinClock, _pin, _ledNumber);
}

void LedComponent::setColor(LedNumber led_number, Color color)
{
    _led->setColorRGB(static_cast<byte>(led_number), color.red, color.green, color.blue);
}

void LedComponent::setColor(LedNumber led_number, Color color, uint16_t fading_time)
{
    const auto redFade = color.red / (static_cast<float>(fading_time));
    const auto greenFade = color.green / (static_cast<float>(fading_time));
    const auto blueFade = color.blue / (static_cast<float>(fading_time));

    for (uint16_t time(0); time < fading_time; time++)
    {
        _led->setColorRGB(static_cast<byte>(led_number), static_cast<byte>(redFade * time), static_cast<byte>(greenFade * time), static_cast<byte>(blueFade * time));
        delay(1);
    }
}