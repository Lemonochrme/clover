#ifndef _HEADER_SCREEN_COMPONENTS
#define _HEADER_SCREEN_COMPONENTS
#include <WString.h>
#include <vector>
#include <U8g2lib.h>

namespace Display
{
    // Enums
    enum class StyleWidth
    {
        LEFT,
        CENTERED,
        RIGHT
    };

    enum class StyleHeight
    {
        TOP,
        CENTERED,
        BOTTOM
    };

    // TextBox which inherits from Box (Single Component)
    class TextBox
    {
    public:
        TextBox(String str, StyleWidth sw, u8g2_uint_t style);
        uint16_t getX();
        const char * getString();
        void updateString(String str);
        u8g2_uint_t getStyle();
        uint16_t getTextWidth();
        StyleWidth getStyleWidth();
    private:
        void Calculate();
        String _text;
        uint8_t *_font;
        u8g2_uint_t _style;
        StyleWidth _styleWidth;
        uint16_t _x;
        uint16_t _textWidth;
    };

    // Components which contains every type
    class Components
    {
    public:
        Components();
        void Add(TextBox box);
        void Add(std::vector<TextBox> boxes);
        void Update(size_t index, String text);
        void Display(StyleHeight sh=StyleHeight::TOP, uint16_t offset=0, uint16_t padding=0);
    private:
        // Boxes
        std::vector<TextBox> _boxes;
    };
};

#endif //_HEADER_SCREEN_COMPONENTS