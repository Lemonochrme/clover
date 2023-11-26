#ifndef _HEADER_SCREEN
#define _HEADER_SCREEN
#include <U8g2lib.h>
#include <Wire.h>

#include "ScreenComponents.hpp"

namespace Display
{
    constexpr uint8_t FONT_SIZE=8;

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
        void Setup(uint8_t *font);
        void connecting(uint8_t state = 0);
        void connected(const char *ipaddress);
        void loop();
        // Getters
        uint16_t getHeight();
        uint16_t getWidth();
        U8G2_SSD1306_128X64_NONAME_F_HW_I2C& getScreen();
        uint16_t getTextWidth(const char * str);
    private:
        // Singleton
        Screen();
        ~Screen();
        Screen(const Screen &) = delete;
        Screen &operator=(const Screen &) = delete;

        // Fonctions
        uint16_t setupHeader(const uint16_t w_padding = 2, const uint16_t h_padding = 5);
        
        // Variables
        U8G2_SSD1306_128X64_NONAME_F_HW_I2C *_screen;
        uint8_t *_font;
        uint16_t _width;
        uint16_t _height;

        // Static Components
        Components connectingWindow;
        Components connectedWindow;
    };
}

#endif //_HEADER_SCREEN