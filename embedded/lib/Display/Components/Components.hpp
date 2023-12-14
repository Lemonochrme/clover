#ifndef _HEADER_DISPLAY_COMPONENTS
#define _HEADER_DISPLAY_COMPONENTS
#include <vector>
#include <memory>
#include "Box.hpp"

namespace Display
{
    class Components
    {
    public:
        Components();
        void Add(std::shared_ptr<Box> box);
        void Add(std::vector<std::shared_ptr<Box>> boxes);
        void Update(size_t index, std::any modified);
        void Display();
    private:
        size_t GetSize(StyleHeight sh);
        // Boxes
        std::vector<std::shared_ptr<Box>> _boxes;
    };
};

#endif //_HEADER_DISPLAY_COMPONENTS