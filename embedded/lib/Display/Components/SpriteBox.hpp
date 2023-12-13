#ifndef _HEADER_DISPLAY_SPRITEBOX
#define _HEADER_DISPLAY_SPRITEBOX
#include "Box.hpp"

namespace Display
{
    struct Picture {
        unsigned char* data;
        uint16_t width;
        uint16_t height;
    };

    class SpriteBox : public Box
    {
    public:
        SpriteBox();
        /**
         * @brief Construct a new Text Box object
         *
         * @param sprite array from an .xbm format
         */
        SpriteBox(unsigned char *sprite, uint16_t width, uint16_t height, StyleWidth sw, StyleHeight sh);
        void Display(u8g2_uint_t size, u8g2_uint_t size_pos) override;
        
        /**
         * @brief Updates sprite
         * 
         * @param data unsigned char*
         */
        void Update(std::any data) override;

    private:
        void Calculate();
        unsigned char* _sprite;
        StyleWidth _styleWidth;
        uint16_t _width;
        uint16_t _height;
        uint16_t _x;
    };
}

#endif //_HEADER_DISPLAY_SPRITEBOX