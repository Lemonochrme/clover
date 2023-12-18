#ifndef _HEADER_MOISTURE
#define _HEADER_MOISTURE

#include "MainComponent.hpp"
#include <stdint.h>

/**
 * @brief See the documentation on 'https://www.mouser.com/datasheet/2/744/Seeed_101020008-1217463.pdf'
 */
namespace MoistureLevel {
    constexpr uint16_t AIR = 0;
    constexpr uint16_t DRY = 300;
    constexpr uint16_t HUMID = 700;
    constexpr uint16_t WATER = 950;
}

enum class LedMoistureStatus {
    IDLE,
    WARNING,
};

void plantLedLoop(float soilHumidity);

#endif // _HEADER_MOISTURE