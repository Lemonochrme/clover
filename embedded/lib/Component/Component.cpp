#include "Component.hpp"

Component::Component(ComponentType ct, uint8_t p)
: _type(ct), _pin(p) 
{}

std::any Component::getValue(void){
    switch(_type)
    {
        case ComponentType::Digital:
            return digitalRead(_pin);
        case ComponentType::Analog:
            return analogRead(_pin);
        default:
            return 0;
    }
}

void Component::sendValue(std::any data)
{
    switch(_type) {
        case ComponentType::Digital:
            digitalWrite(_pin, std::any_cast<uint8_t>(data));
        case ComponentType::Analog:
            analogWrite(_pin, std::any_cast<int>(data));
    }
}