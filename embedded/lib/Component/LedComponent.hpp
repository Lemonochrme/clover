#ifndef _HEADER_COMPONENT_LED
#define _HEADER_COMPONENT_LED
#include "Component.hpp"
#include <ChainableLED.h>

struct Color
{
    byte red;
    byte blue;
    byte green;

    Color operator-(byte value);
};

namespace LedColors
{
    constexpr Color LED_OFF = {0,0,0};
    constexpr Color WIFI_ON = {0x18,0x28,0x36};
    constexpr Color NO_WIFI = {0x64,0x04,0x0B};
}

class LedComponent
{
public:
    LedComponent(byte pin, byte pin_clock, uint8_t led_number);
    ~LedComponent();
    void setup();
    void setColor(uint8_t led_number, Color color);
    void setColor(uint8_t led_number, Color color, uint16_t fading_time);

private:
    byte _pin;
    byte _pinClock;
    uint8_t _ledNumber;
    ChainableLED* _led;
};

#endif // _HEADER_COMPONENT_LED