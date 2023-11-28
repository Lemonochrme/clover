#ifndef _HEADER_DISPLAY_TEXTBOX
#define _HEADER_DISPLAY_TEXTBOX
#include "Box.hpp"

namespace Display
{

    class TextBox : public Box
    {
    public:
        TextBox();
        /**
         * @brief Construct a new Text Box object
         * 
         * @param str the string to display
         * @param sw style width (LEFT, CENTERED, RIGHT)
         * @param sh style height (TOP, CENTERED, BOTTOM)
         * @param style u8g2lib button style (see doc @ )
         * @param w_padding width padding (default: 0)
         * @param h_padding height padding (default: 0)
         * @param takeWholeLine if true, the button takes the whole line
         */
        TextBox(String str, StyleWidth sw, StyleHeight sh, u8g2_uint_t style, u8g2_uint_t w_padding=0, u8g2_uint_t h_padding=0, bool takeWholeLine=false);
        void Display(size_t size, size_t position, u8g2_uint_t offsetY) override;
        void Update(String str) override;
        StyleHeight getStyleHeight() override;
        u8g2_uint_t getPadding() override;
    private:
        void Calculate();
        String _text;
        uint8_t *_font;
        u8g2_uint_t _style;
        u8g2_uint_t _paddingWidth;
        u8g2_uint_t _paddingHeight;
        StyleWidth _styleWidth;
        StyleHeight _styleHeight;
        uint16_t _x;
        uint16_t _textWidth;
        bool _takeWholeLine;
    };
}

#endif //_HEADER_DISPLAY_TEXTBOX