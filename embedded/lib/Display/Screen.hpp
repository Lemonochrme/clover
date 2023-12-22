#ifndef _HEADER_SCREEN
#define _HEADER_SCREEN
#include <U8g2lib.h>
#include <Wire.h>

#include "Components/Components.hpp"
#include "Components/TextBox.hpp"
#include "Components/SpriteBox.hpp"

// Frame for booting
#include "../Pictures/clover1.xbm"
#include "../Pictures/clover2.xbm"
#include "../Pictures/clover3.xbm"
#include "../Pictures/clover4.xbm"
#include "../Pictures/clover5.xbm"
#include "../Pictures/clover6.xbm"
#include "../Pictures/clover7.xbm"
#include "../Pictures/clover8.xbm"
#include "../Pictures/clover9.xbm"
#include "../Pictures/clover10.xbm"
#include "../Pictures/clover11.xbm"

// Icons
#include "../Pictures/humidity.xbm"
#include "../Pictures/thermometer.xbm"
#include "../Pictures/air_humidity.xbm"
#include "../Pictures/humidity-warning.xbm"
#include "../Pictures/thermometer-warning.xbm"
#include "../Pictures/air_humidity-warning.xbm"

namespace Display
{
    /**
     * @brief Each frame of the clover boot animation
     */
    constexpr Picture CLOVER_FRAMES[] = {
        {clover1_bits, clover1_width, clover1_height},
        {clover2_bits, clover2_width, clover2_height},
        {clover3_bits, clover3_width, clover3_height},
        {clover4_bits, clover4_width, clover4_height},
        {clover5_bits, clover5_width, clover5_height},
        {clover6_bits, clover6_width, clover6_height},
        {clover7_bits, clover7_width, clover7_height},
        {clover8_bits, clover8_width, clover8_height},
        {clover9_bits, clover9_width, clover9_height},
        {clover10_bits, clover10_width, clover10_height},
        {clover11_bits, clover11_width, clover11_height},
    };

    /**
     * @brief Icons per component
     */
    constexpr Picture ICONS[] = {
        {humidity_bits,humidity_width,humidity_height},
        {thermometer_bits,thermometer_width,thermometer_height},
        {air_humidity_bits,air_humidity_width,air_humidity_height},
    };

    /**
     * @brief Icons per component (warning variant)
     */
    constexpr Picture ICONS_WARNING[] = {
        {humidity_warning_bits,humidity_warning_width,humidity_warning_height},
        {thermometer_warning_bits,thermometer_warning_width,thermometer_warning_height},
        {air_humidity_warning_bits,air_humidity_warning_width,air_humidity_warning_height},
    };

    // Const from the Screen
    constexpr uint8_t MAX_BOOT_FRAMES = 25;
    constexpr uint8_t OFFSET_ICONS = 55;
    constexpr uint8_t OFFSET_TEXT = 75;

    /**
     * @brief Used for the pictures icons. Each icon has an index linked to a sensor
     */
    enum class Sensors {
        SOIL_MOISTURE = 0,
        THERMOMETER,
        AIR_HUMIDITY
    };

    class Screen
    {
    public:
        // Singleton
        static Screen &GetInstance()
        {
            static Screen instance;
            return instance;
        }
        // Public functions

        /**
         * @brief To be called when the setup() of the Arduino library finished
         * 
         * @param font font from the U8G2 library. 
         */
        void Setup(uint8_t *font);

        /**
         * @brief Screen to display when connecting
         * 
         * @param state from 0 to 3, shows little dots at the end of the text
         */
        void connecting(uint8_t state=0);

        /**
         * @brief Screen to display when not connected
         */
        void notConnected();

        /**
         * @brief Screen to display when connected, a little loading bar is showed.
         * ! Should use the latest Component Library
         * 
         * @param ipaddress text to display, an IpAdress is recommended, but it can be a complete URL
         * @param timing if equals 0, stop the loading.
         */
        void connected(const char *ipaddress, uint8_t timing);

        /**
         * @brief Screen bootscreen
         */
        void boot();

        /**
         * @brief Screen for the main loop with the sensors information
         * 
         * @param plantHumidity must be a percentage
         * @param airTemperature must not exceed 99°C
         * @param airHumidity must be a percentage
         */
        void loop(const float plantHumidity, const float airTemperature, const float airHumidity);

        /**
         * @brief Set the Warning Icon for a given sensor
         * 
         * @param sensorId the sensor to change icon
         * @param warning if precised as false, will reset the normal icon
         */
        void setWarningIcon(Sensors sensorId, bool warning=true);

        // Getters
        /**
         * @brief Get the Height of the Screen
         * 
         * @return uint16_t 
         */
        uint16_t getHeight();

        /**
         * @brief Get the Width of the Screen
         * 
         * @return uint16_t 
         */
        uint16_t getWidth();

        /**
         * @brief Get the Screen object
         * 
         * @return U8G2_SSD1306_128X64_NONAME_F_HW_I2C& 
         */
        U8G2_SSD1306_128X64_NONAME_F_HW_I2C& getScreen();

        /**
         * @brief Get the Text Width from a given string
         * 
         * @param str 
         * @return uint16_t depending on the font size, get the text width
         */
        uint16_t getTextWidth(const char * str);

        /** 
         * @return true if the bootscreen havent finished
         * @return false if the bootscreen finished
         */
        bool isBooting();
    private:
        // Singleton
        Screen();
        ~Screen();
        Screen(const Screen &) = delete;
        Screen &operator=(const Screen &) = delete;
        
        // Variables
        U8G2_SSD1306_128X64_NONAME_F_HW_I2C *_screen;
        uint8_t *_font;
        uint16_t _width;
        uint16_t _height;
        String _loading;
        // Extern
        uint8_t _bootFrame;
        bool _booted;

        // Static Components
        Components connectingWindow;
        Components connectionfailedWindow;
        Components connectedWindow;
        Components bootWindow;
        Components loopWindow;
        Components iconWindow;
    };
}

#endif //_HEADER_SCREEN