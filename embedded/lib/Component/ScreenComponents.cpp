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
    _boxes[index].updateString(text);
}

void Components::Display(StyleHeight sh, uint16_t offset, uint16_t padding)
{
    const auto totalTextSize = _boxes.size() * FONT_SIZE;
    const auto centeredOffset = (Screen::GetInstance().getHeight() - totalTextSize) - offset;
    for (size_t i = 0; i < _boxes.size(); i++)
    {
        const auto x = (_boxes[i].getStyleWidth() == StyleWidth::CENTERED) ? _boxes[i].getX() : _boxes[i].getX()+padding*i;
        switch (sh)
        {
        case StyleHeight::TOP:
            Screen::GetInstance().getScreen().drawButtonUTF8(x, (i * FONT_SIZE)+offset+padding*i, _boxes[i].getStyle(), _boxes[i].getTextWidth(), padding, padding, _boxes[i].getString());
            break;
        case StyleHeight::CENTERED:
            Screen::GetInstance().getScreen().drawButtonUTF8(x, ((centeredOffset / 2)+i*FONT_SIZE)+offset+padding*i, _boxes[i].getStyle(), _boxes[i].getTextWidth(), padding, padding, _boxes[i].getString());
            break;
        case StyleHeight::BOTTOM:
            Screen::GetInstance().getScreen().drawButtonUTF8(x, (centeredOffset + i * FONT_SIZE)+offset+padding*i, _boxes[i].getStyle(), _boxes[i].getTextWidth(), padding, padding, _boxes[i].getString());
            break;
        }
    }
}

TextBox::TextBox(String str, StyleWidth sw, u8g2_uint_t style)
    : _text(str), _style(style), _styleWidth(sw)
{
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

uint16_t TextBox::getX() { return _x; }
const char *TextBox::getString() { return _text.c_str(); }
void TextBox::updateString(String str)
{
    _text = str;
    Calculate();
}
u8g2_uint_t TextBox::getStyle() { return _style; }
uint16_t TextBox::getTextWidth() { return _textWidth; }
StyleWidth TextBox::getStyleWidth() { return _styleWidth; }