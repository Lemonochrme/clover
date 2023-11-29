#ifndef _HEADER_DISPLAY_BOX
#define _HEADER_DISPLAY_BOX
#include <U8g2lib.h>

namespace Display
{
    /** Size of the actual font from Screen. Used for many calculations
     * ! Must be changed if the _font size is updated
     */
    constexpr uint8_t FONT_SIZE = 8;

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
        BOTTOM
    };

    /**
     * @brief Box is a virtual class which can be derived into many box elements
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
        Box(StyleHeight sh, u8g2_uint_t h_padding)
            : _styleHeight(sh), _paddingHeight(h_padding){};

        /**
         * @brief Used to display the element on the screen.
         * Will be using any Display function from the U8g2lib.
         * ! Maybe a font will be added to arguments next...
         *
         * @param size the total size of the elements from a styleheight
         * @param position the actual position of the element depending of the previous size
         * @param offsetY an offset in Y, given by the 'Components'
         */
        virtual void Display(size_t size, size_t position, u8g2_uint_t offsetY){};

        /**
         * @brief Will update by recalculating the 'Box' constants
         * with the given argument.
         * ! Will be modified in the near future to accept a template, or an std::any
         *
         * @param str
         */
        virtual void Update(String str){};

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

    protected:
        StyleHeight _styleHeight;
        u8g2_uint_t _paddingHeight;
    };
}

#endif //_HEADER_DISPLAY_BOX