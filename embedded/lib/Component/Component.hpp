#ifndef _HEADER_COMPONENT
#define _HEADER_COMPONENT
#include <Arduino.h>
#include <any>

enum class ComponentType {
    Digital,
    Analog,
    I2C,
    Serial
};

class Component{
    public:
        Component(ComponentType ct, uint8_t p);
        std::any getValue();
        void sendValue(std::any data);
    private:
        ComponentType _type;
        const uint8_t _pin;
};

#endif //_HEADER_COMPONENT