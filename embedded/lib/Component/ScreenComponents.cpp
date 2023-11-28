#include "ScreenComponents.hpp"
#include "Screen.hpp"
#include <U8g2lib.h>

using namespace Display;

Components::Components()
{
}

void Components::Add(TextBox box)
{
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
    const auto size_boxes = _boxes.size();
    size_t i(0);
    for(auto it = _boxes.begin() ; it!= _boxes.end() ;it++)
    {
        it->Display(size_boxes,i);
        if (it+1 != _boxes.end() && ((it+1)->getStyleHeight() == it->getStyleHeight()))
            i++;
        else
            i=0;
    }
}

TextBox::TextBox()
{}

TextBox::TextBox(String str, StyleWidth sw, StyleHeight sh, u8g2_uint_t style)
    : _text(str), _style(style), _styleWidth(sw), _styleHeight(sh)
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
    _textWidth = Screen::GetInstance().getTextWidth(_text.c_str());
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

void TextBox::Display(size_t size, size_t position)
{
    const auto centeredOffset = (Screen::GetInstance().getHeight() - (size * FONT_SIZE));
    // Later will be used with padding/margin
    const auto x = (_styleWidth == StyleWidth::CENTERED) ? _x : _x;
    switch (_styleHeight)
    {
    case StyleHeight::TOP:
        Screen::GetInstance().getScreen().drawButtonUTF8(x, (position+1)*FONT_SIZE, _style, _textWidth, 0, 0, _text.c_str());
        break;
    case StyleHeight::CENTERED:
        Screen::GetInstance().getScreen().drawButtonUTF8(x, static_cast<uint16_t>((centeredOffset/2)) + (position+1)*FONT_SIZE, _style, _textWidth, 0, 0, _text.c_str());
        break;
    case StyleHeight::BOTTOM:
        Screen::GetInstance().getScreen().drawButtonUTF8(x, centeredOffset + (position+1)*FONT_SIZE, _style, _textWidth, 0, 0, _text.c_str());
        break;
    }
}

StyleHeight TextBox::getStyleHeight() { return _styleHeight; }