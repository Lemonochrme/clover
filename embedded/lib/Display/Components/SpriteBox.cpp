#include "../Screen.hpp"
#include "SpriteBox.hpp"

using namespace Display;

SpriteBox::SpriteBox()
    :Box(StyleHeight::UNDEFINED,0,0)
{}

SpriteBox::SpriteBox(unsigned char *sprite, uint16_t width, uint16_t height, StyleWidth sw, StyleHeight sh)
    :Box(sh,0,height)
    , _sprite(sprite)
    , _styleWidth(sw)
    , _width(width)
    , _height(height)
{
    Calculate();
}

void SpriteBox::Update(std::any data)
{
    _sprite = std::any_cast<unsigned char*>(data);
    Calculate();
}

void SpriteBox::Calculate()
{
    const auto screenWidth = Screen::GetInstance().getWidth();
    switch (_styleWidth)
    {
    case StyleWidth::CENTERED:
        _x = (screenWidth - _width) / 2;
        break;
    case StyleWidth::RIGHT:
        _x = screenWidth - _width;
        break;
    default:
        _x = 0;
    }
}

void SpriteBox::Display(u8g2_uint_t size, u8g2_uint_t size_pos)
{
    const auto centeredOffset = (Screen::GetInstance().getHeight() - size);
    switch(this->_styleHeight)
    {
    case StyleHeight::CENTERED:
        // idk must be the size of all the above 
        Screen::GetInstance().getScreen().drawXBM(_x, static_cast<uint16_t>((centeredOffset / 2)) + size_pos,_width,_height,_sprite);
        break;
    case StyleHeight::BOTTOM:
        Screen::GetInstance().getScreen().drawXBM(_x, centeredOffset + size_pos,_width,_height,_sprite);
        break;
    default:
        Screen::GetInstance().getScreen().drawXBM(_x, size_pos,_width,_height,_sprite);
    }
}