#include "../Screen.hpp"
#include "SpriteBox.hpp"

using namespace Display;

SpriteBox::SpriteBox()
    :Box(StyleHeight::UNDEFINED,0)
{}

SpriteBox::SpriteBox(unsigned char *sprite, uint16_t width, uint16_t height, u8g2_uint_t x, u8g2_uint_t y)
    :Box(StyleHeight::TOP,0)
    , _sprite(sprite)
    , _width(width)
    , _height(height)
    , _x(x)
    , _y(y)
{}

void SpriteBox::Update(std::any data)
{
    _sprite = std::any_cast<unsigned char*>(data);
}

void SpriteBox::Display(size_t size, size_t position, u8g2_uint_t offsetY)
{
    Screen::GetInstance().getScreen().drawXBM(_x,_y,_width,_height,_sprite);
}