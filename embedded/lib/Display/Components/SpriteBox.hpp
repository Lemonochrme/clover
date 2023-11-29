#ifndef _HEADER_DISPLAY_SPRITEBOX
#define _HEADER_DISPLAY_SPRITEBOX
#include "Box.hpp"

namespace Display
{

    class SpriteBox : public Box
    {
    public:
        SpriteBox();
        /**
         * @brief Construct a new Text Box object
         *
         * @param sprite array from an .xbm format
         */
        SpriteBox(unsigned char *sprite, uint16_t width, uint16_t height, u8g2_uint_t x=0, u8g2_uint_t y=0);
        void Display(size_t size, size_t position, u8g2_uint_t offsetY) override;
        
        /**
         * @brief Updates sprite
         * 
         * @param data unsigned char*
         */
        void Update(std::any data) override;

    private:
        unsigned char* _sprite;
        uint16_t _width;
        uint16_t _height;
        u8g2_uint_t _x;
        u8g2_uint_t _y;
    };
}

#endif //_HEADER_DISPLAY_SPRITEBOX