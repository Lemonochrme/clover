#include "../Screen.hpp"
#include "TextBox.hpp"

using namespace Display;

TextBox::TextBox()
    : Box(StyleHeight::UNDEFINED, 0, 0)
{
}

TextBox::TextBox(String str, StyleWidth sw, StyleHeight sh, u8g2_uint_t style, u8g2_uint_t w_padding, u8g2_uint_t h_padding, bool takeWholeLine)
    : Box(sh, h_padding, FONT_SIZE), _text(str), _style(style), _paddingWidth(w_padding), _styleWidth(sw), _takeWholeLine(takeWholeLine)
{
    Calculate();
}

void TextBox::Update(std::any data)
{
    _text = std::any_cast<String>(data);
    Calculate();
}

void TextBox::Calculate()
{
    const auto width = Screen::GetInstance().getWidth();
    _textWidth = _takeWholeLine ? width : Screen::GetInstance().getTextWidth(_text.c_str());
    switch (_styleWidth)
    {
    case StyleWidth::LEFT:
        _x = 0;
        break;
    case StyleWidth::CENTERED:
        _x = (width - _textWidth) / 2;
        break;
    case StyleWidth::RIGHT:
        _x = width - _textWidth;
        break;
    default:
        _x = 0;
    }
}

void TextBox::Display(size_t size, size_t size_pos, u8g2_uint_t offsetY)
{
    const auto centeredOffset = (Screen::GetInstance().getHeight() - size);
    switch (this->_styleHeight)
    {
    case StyleHeight::CENTERED:
        Screen::GetInstance().getScreen().drawButtonUTF8(_paddingWidth + _x, static_cast<uint16_t>((centeredOffset / 2)) + size_pos + offsetY, _style, _textWidth, this->_paddingHeight, _paddingWidth, _text.c_str());
        break;
    case StyleHeight::BOTTOM:
        Screen::GetInstance().getScreen().drawButtonUTF8(_paddingWidth + _x, centeredOffset + size_pos + offsetY, _style, _textWidth, this->_paddingHeight, _paddingWidth, _text.c_str());
        break;
    default:
        Screen::GetInstance().getScreen().drawButtonUTF8(_paddingWidth + _x, size_pos + offsetY, _style, _textWidth, this->_paddingHeight, _paddingWidth, _text.c_str());
    }
}