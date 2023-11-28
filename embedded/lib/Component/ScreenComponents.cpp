#include "ScreenComponents.hpp"
#include "Screen.hpp"
#include <U8g2lib.h>

using namespace Display;

Components::Components()
{
}

void Components::Add(TextBox box)
{
    // When Added, boxes should be reordered by style.
    _boxes.push_back(box);
}

void Components::Add(std::vector<TextBox> boxes)
{
    for (auto box : boxes)
    {
        _boxes.push_back(box);
    }
}

void Components::Update(size_t index, String text)
{
    _boxes[index].Update(text);
}

void Components::Display()
{
    size_t i(0);
    u8g2_uint_t verticalPadding(0);
    for (auto it = _boxes.begin(); it != _boxes.end(); it++)
    {
        const auto size_boxes = GetSize(it->getStyleHeight());
        it->Display(size_boxes, i, verticalPadding);
        // Index and verticalPadding only incrementing for the same style. (eg : it and it+1 as the same style.)
        if (it + 1 != _boxes.end() && ((it + 1)->getStyleHeight() == it->getStyleHeight()))
        {
            verticalPadding += it->getPadding();
            i++;
        }
        else
        {
            verticalPadding = 0;
            i = 0;
        }
    }
}

size_t Components::GetSize(StyleHeight sh)
{
    size_t returnSize(0);
    // returnSize is equal to FONT_SIZE + vertical padding * boxes with style sh
    for(auto& box : _boxes)
        returnSize += (box.getStyleHeight() == sh ? (FONT_SIZE+box.getPadding()) : 0);
    return returnSize;
}

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
    }
}

StyleHeight TextBox::getStyleHeight() { return _styleHeight; }
u8g2_uint_t TextBox::getPadding() { return _paddingHeight; }