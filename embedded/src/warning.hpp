#ifndef _HEADER_WARNING
#define _HEADER_WARNING

#include <stdint.h>

namespace Warning {
    /**
     * @brief See the documentation on 'https://www.mouser.com/datasheet/2/744/Seeed_101020008-1217463.pdf'
     */
    namespace MoistureLevel {
        constexpr uint16_t AIR = 0;
        constexpr uint16_t DRY = 300;
        constexpr uint16_t HUMID = 700;
        constexpr uint16_t WATER = 950;
    }
    constexpr float AIR_HUMIDITY_SATURATED = 95.0f;
    /**
     * @brief Source : 'https://extension.umd.edu/resource/temperature-and-humidity-indoor-plants/'
     */
    constexpr float AIR_TEMPERATURE_TOO_HOT = 29.0f;
    constexpr float AIR_TEMPERATURE_TOO_COLD = 14.0f;

    enum class LedMoistureStatus {
        IDLE,
        DRY,
        WET
    };

    void warningLedLoop(const float soilHumidity);
    void warningScreenLoop(const float plantMoisture, const float airTemperature, const float airHumidity);
}

#endif // _HEADER_WARNING