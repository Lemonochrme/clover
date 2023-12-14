#ifndef _HEADER_DISPLAY_BOX
#define _HEADER_DISPLAY_BOX
#include <U8g2lib.h>
#include <any>

namespace Display
{
    /**
     * @brief Where each Box element is centered on the x axis.
     */
    enum class StyleWidth
    {
        UNDEFINED,
        LEFT,
        CENTERED,
        RIGHT
    };

    /**
     * @brief Each Box element can be ordered into heights.
     * Each height is independent from another and is placed differently on the screen.
     * TOP starts on x=0, CENTERED on x=height/2 and TOP x=height
     */
    enum class StyleHeight
    {
        UNDEFINED,
        TOP,
        CENTERED,
        BOTTOM,
        FORCE_CENTERED
    };

    /**
     * @brief Box is an abstract class which can be derived into many box elements
     * and will be used in the 'Components' object.
     * It is composed of 4 functions which may or not be used.
     * Each box should use the Screen Interface in the Display function,
     * other functions can be modified to the developer's needs.
     */
    class Box
    {
    public:
        /**
         * @brief Construct a new Box object, can be ignored.
         */
        Box(StyleHeight sh, u8g2_uint_t h_padding, uint16_t height)
            : _styleHeight(sh), _paddingHeight(h_padding), _height(height), _xOffset(0), _yOffset(0){};

        /**
         * @brief Used to display the element on the screen.
         * Will be using any Display function from the U8g2lib.
         * ! Maybe a font will be added to arguments next...
         *
         * @param size the total size of the elements from a styleheight
         * @param size_pos all the above sizes from each components in a same style height plus its height padding
         */
        virtual void Display(u8g2_uint_t size, u8g2_uint_t size_pos){};

        /**
         * @brief Will update by recalculating the 'Box' constants
         * with the given argument.
         *
         * @param data the data to modify, depending on the Box type
         */
        virtual void Update(std::any data){};

        /**
         * @brief Get the Style Height, logic can be changed.
         *
         * @return StyleHeight
         */
        virtual StyleHeight getStyleHeight() { return _styleHeight; };

        /**
         * @brief Get the Padding object, logic can be changed.
         * ? Only vertical/height padding
         *
         * @return u8g2_uint_t
         */
        virtual u8g2_uint_t getPadding() { return _paddingHeight; };

        virtual uint16_t getHeight() { return _height; }

        virtual void SetOffset(uint16_t xOffset, uint16_t yOffset=0)
        {
            _xOffset = xOffset;
            _yOffset = yOffset;
        }

    protected:
        StyleHeight _styleHeight;
        u8g2_uint_t _paddingHeight;
        uint16_t _height;
        uint16_t _xOffset;
        uint16_t _yOffset;
    };
}

#endif //_HEADER_DISPLAY_BOX