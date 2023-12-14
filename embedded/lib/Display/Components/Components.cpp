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

void Components::Update(size_t index, std::any modified)
{
    _boxes[index]->Update(modified);
}

void Components::Display()
{
    u8g2_uint_t  totalSize(0);
    for (auto it = _boxes.begin(); it != _boxes.end(); it++)
    {
        const auto size_boxes = GetSize((*it)->getStyleHeight());
        (*it)->Display(size_boxes, totalSize);

        /*  Index and verticalPadding only incrementing for the same style. (eg : it and it+1 as the same style.)
            Plus, it has to not be FORCED to be incremented.*/
        if (it + 1 != _boxes.end() && ((*(it+1))->getStyleHeight() == (*it)->getStyleHeight()) && ((*it)->getStyleHeight() != StyleHeight::FORCE_CENTERED))
            totalSize += (*it)->getHeight() + (2*(*it)->getPadding());
        else
            totalSize = 0;
    }
}

size_t Components::GetSize(StyleHeight sh)
{
    size_t returnSize(0);
    // returnSize is equal to FONT_SIZE + vertical padding * boxes with style sh
    for(auto& box : _boxes)
        returnSize += (box->getStyleHeight() == sh ? (box->getHeight()+(2*box->getPadding())) : 0);
    return returnSize;
}