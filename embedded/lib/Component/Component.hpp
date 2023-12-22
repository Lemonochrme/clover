#ifndef _HEADER_COMPONENT
#define _HEADER_COMPONENT
#include <Arduino.h>
#include <any>

enum class ComponentType {
    Digital,
    Analog
};

class Component{
    public:
        /**
         * @brief Construct a new Component object
         * 
         * @param ct see ComponentType enum
         * @param p pin conncted to the Component
         */
        Component(ComponentType ct, uint8_t p);

        /**
         * @brief Get the Value as an std::any
         * 
         * @return std::any recast into the type depending on the component
         */
        std::any getValue();

        /**
         * @brief Send the value as an std::any, 
         * 
         * @param data be careful of the component type of the object
         */
        void sendValue(std::any data);
    private:
        ComponentType _type;
        const uint8_t _pin;
};

#endif //_HEADER_COMPONENT