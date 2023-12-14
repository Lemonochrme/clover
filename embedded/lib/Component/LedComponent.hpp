#ifndef _HEADER_COMPONENT_LED
#define _HEADER_COMPONENT_LED
#include "Component.hpp"
#include <ChainableLED.h>

struct Color
{
    byte red;
    byte blue;
    byte green;
};

class LedComponent
{
public:
    LedComponent(byte pin, byte pin_clock, uint8_t led_number);
    ~LedComponent();
    void setup();
    void setColor(uint8_t led_number, Color color);

private:
    byte _pin;
    byte _pinClock;
    uint8_t _ledNumber;
    ChainableLED* _led;
};

#endif // _HEADER_COMPONENT_LED