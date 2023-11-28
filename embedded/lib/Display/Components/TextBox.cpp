#include "../Screen.hpp"
#include "TextBox.hpp"

using namespace Display;

TextBox::TextBox()
{
}

TextBox::TextBox(String str, StyleWidth sw, StyleHeight sh, u8g2_uint_t style, u8g2_uint_t w_padding, u8g2_uint_t h_padding, bool takeWholeLine)
    : _text(str), _style(style), _paddingWidth(w_padding), _paddingHeight(h_padding), _styleWidth(sw), _styleHeight(sh), _takeWholeLine(takeWholeLine)
{
    Calculate();
}

void TextBox::Update(String str)
{
    _text = str;
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
        _x=0;
    }
}

void TextBox::Display(size_t size, size_t position, u8g2_uint_t offsetY)
{
    const auto centeredOffset = (Screen::GetInstance().getHeight() - size);
    // Later will be used with padding/margin
    const auto x = (_styleWidth == StyleWidth::CENTERED) ? _x : _x;
    switch (_styleHeight)
    {
    case StyleHeight::TOP:
        Screen::GetInstance().getScreen().drawButtonUTF8(_paddingWidth + x, (position + 1) * FONT_SIZE + offsetY, _style, _textWidth, _paddingHeight, _paddingWidth, _text.c_str());
        break;
    case StyleHeight::CENTERED:
        Screen::GetInstance().getScreen().drawButtonUTF8(_paddingWidth + x, static_cast<uint16_t>((centeredOffset / 2)) + (position + 1) * FONT_SIZE + offsetY, _style, _textWidth, _paddingHeight, _paddingWidth, _text.c_str());
        break;
    case StyleHeight::BOTTOM:
        Screen::GetInstance().getScreen().drawButtonUTF8(_paddingWidth + x, centeredOffset + (position + 1) * FONT_SIZE + offsetY, _style, _textWidth, _paddingHeight, _paddingWidth, _text.c_str());
        break;
    default:
        break;
    }
}

StyleHeight TextBox::getStyleHeight() { return _styleHeight; }
u8g2_uint_t TextBox::getPadding() { return _paddingHeight; }