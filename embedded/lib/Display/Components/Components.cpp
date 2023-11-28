#include "Components.hpp"

using namespace Display;

Components::Components()
{
}

void Components::Add(std::shared_ptr<Box> box)
{
    // When Added, boxes should be reordered by style.
    _boxes.push_back(box);
}

void Components::Add(std::vector<std::shared_ptr<Box>> boxes)
{
    for (auto box : boxes)
    {
        _boxes.push_back(box);
    }
}

void Components::Update(size_t index, String text)
{
    _boxes[index]->Update(text);
}

void Components::Display()
{
    size_t i(0);
    u8g2_uint_t verticalPadding(0);
    for (auto it = _boxes.begin(); it != _boxes.end(); it++)
    {
        const auto size_boxes = GetSize((*it)->getStyleHeight());
        (*it)->Display(size_boxes, i, verticalPadding);
        // Index and verticalPadding only incrementing for the same style. (eg : it and it+1 as the same style.)
        if (it + 1 != _boxes.end() && ((*(it+1))->getStyleHeight() == (*it)->getStyleHeight()))
        {
            verticalPadding += (*it)->getPadding();
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
        returnSize += (box->getStyleHeight() == sh ? (FONT_SIZE+box->getPadding()) : 0);
    return returnSize;
}