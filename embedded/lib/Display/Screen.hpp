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

namespace Display
{
    constexpr Picture clover_frames[] = {
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
        void connecting(uint8_t state=0);
        void notConnected();
        void connected(const char *ipaddress, uint8_t timing);
        void boot();
        void loop();
        // Getters
        uint16_t getHeight();
        uint16_t getWidth();
        U8G2_SSD1306_128X64_NONAME_F_HW_I2C& getScreen();
        uint16_t getTextWidth(const char * str);
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
        TextBox headerSetup;
        Components connectingWindow;
        Components connectionfailedWindow;
        Components connectedWindow;
        Components bootWindow;
        Components loopWindow;
    };
}

#endif //_HEADER_SCREEN