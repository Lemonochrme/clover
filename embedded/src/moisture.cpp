#include "moisture.hpp"

LedMoistureStatus moisture_status(LedMoistureStatus::IDLE);

void plantLedLoop(float soilHumidity)
{
    auto& led = MainComponent::GetInstance().getLed();

    if ((soilHumidity < MoistureLevel::DRY) && (moisture_status == LedMoistureStatus::IDLE))
    {
        moisture_status = LedMoistureStatus::WARNING;
        led.setColor(LedNumber::LED_PLANT,LedColors::TOO_DRY,200);
    }
    else if (soilHumidity >= MoistureLevel::DRY && soilHumidity < MoistureLevel::HUMID)
    {
        led.setColor(LedNumber::LED_PLANT,LedColors::LED_OFF);
        moisture_status = LedMoistureStatus::IDLE;
    }
    else if (moisture_status == LedMoistureStatus::IDLE)
    {
        moisture_status = LedMoistureStatus::WARNING;
        led.setColor(LedNumber::LED_PLANT,LedColors::TOO_WET,200);
    }
}