#ifndef _HEADER_COMPONENT_LED
#define _HEADER_COMPONENT_LED
#include "Component.hpp"
#include <ChainableLED.h>

/**
 * @brief Color composed of multiple bytes, rgb
 */
struct Color
{
    byte red;
    byte green;
    byte blue;

    Color operator-(byte value);
};

/**
 * @brief a set of colors to use when powering the led
 */
namespace LedColors
{
    constexpr Color LED_OFF = {0,0,0};
    constexpr Color WIFI_ON = {0x18,0x28,0x36};
    constexpr Color NO_WIFI = {0x64,0x04,0x0B};
    constexpr Color TOO_DRY = {0xB3,0x58,0x1B};
    constexpr Color TOO_WET = {0x1B,0x09,0x3F};
}

/**
 * @brief ENUM for the two used LED
 */
enum class LedNumber {
    LED_HARDWARE = 0,
    LED_PLANT = 1
};

class LedComponent
{
public:
    /**
     * @brief Construct a new Led Component object
     * 
     * @param pin the pin used to communicate with the LED
     * @param pin_clock the pin clock with the chainable LED
     * @param led_number number of LED in the chain
     */
    LedComponent(byte pin, byte pin_clock, uint8_t led_number);
    ~LedComponent();

    /**
     * @brief called once the setup() is done in Arduino
     */
    void setup();

    /**
     * @brief Set the Color of the LED. 
     * 
     * @param led_number Selecting the LED to light up
     * @param color Color of the LED
     */
    void setColor(LedNumber led_number, Color color);

    /**
     * @brief Set the Color of the LED.
     * 
     * @param led_number Selecting the LED to light up
     * @param color Color of the LED
     * @param fading_time From 0,0,0 to the Color
     */
    void setColor(LedNumber led_number, Color color, uint16_t fading_time);

private:
    byte _pin;
    byte _pinClock;
    uint8_t _ledNumber;
    ChainableLED* _led;
};

#endif // _HEADER_COMPONENT_LED