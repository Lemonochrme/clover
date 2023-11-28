#ifndef _HEADER_DISPLAY_BOX
#define _HEADER_DISPLAY_BOX
#include <U8g2lib.h>

namespace Display
{
    // Global Constants
    constexpr uint8_t FONT_SIZE = 8;

    // Enums
    enum class StyleWidth
    {
        UNDEFINED,
        LEFT,
        CENTERED,
        RIGHT
    };

    enum class StyleHeight
    {
        UNDEFINED,
        TOP,
        CENTERED,
        BOTTOM
    };

    class Box
    {
    public:
        Box() {};
        virtual void Display(size_t size, size_t position, u8g2_uint_t offsetY) {};
        virtual void Update(String str) {};
        virtual StyleHeight getStyleHeight() { return StyleHeight::UNDEFINED; };
        // Only vertical/height padding
        virtual u8g2_uint_t getPadding() { return 0; };
    };
}

#endif //_HEADER_DISPLAY_BOX