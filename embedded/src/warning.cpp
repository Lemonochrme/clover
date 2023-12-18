#include "warning.hpp"

#include "Screen.hpp"
#include "MainComponent.hpp"

using namespace Warning;

LedMoistureStatus moisture_status(LedMoistureStatus::IDLE);

void Warning::warningLedLoop(const float soilHumidity)
{
    auto& led = MainComponent::GetInstance().getLed();

    if ((soilHumidity < MoistureLevel::DRY) && (moisture_status != LedMoistureStatus::DRY))
    {
        moisture_status = LedMoistureStatus::DRY;
        led.setColor(LedNumber::LED_PLANT,LedColors::TOO_DRY,200);
    }
    else if (soilHumidity >= MoistureLevel::DRY && soilHumidity < MoistureLevel::HUMID)
    {
        led.setColor(LedNumber::LED_PLANT,LedColors::LED_OFF);
        moisture_status = LedMoistureStatus::IDLE;
    }
    else if ((soilHumidity >= MoistureLevel::HUMID) && (moisture_status != LedMoistureStatus::WET))
    {
        moisture_status = LedMoistureStatus::WET;
        led.setColor(LedNumber::LED_PLANT,LedColors::TOO_WET,200);
    }
}

void Warning::warningScreenLoop(const float plantMoisture, const float airTemperature, const float airHumidity)
{
    auto& display = Display::Screen::GetInstance();

    // Plant Moisture Warning
    if(plantMoisture < MoistureLevel::DRY || plantMoisture > MoistureLevel::HUMID)
        display.setWarningIcon(Display::Sensors::SOIL_MOISTURE);
    else
        display.setWarningIcon(Display::Sensors::SOIL_MOISTURE,false);

    // Temperature Warning
    if(airTemperature >= AIR_TEMPERATURE_TOO_HOT || airTemperature <= AIR_TEMPERATURE_TOO_COLD)
        display.setWarningIcon(Display::Sensors::THERMOMETER);
    else
        display.setWarningIcon(Display::Sensors::THERMOMETER,false);

    // Humidity Warning
    if(airHumidity >= AIR_HUMIDITY_SATURATED)
        display.setWarningIcon(Display::Sensors::AIR_HUMIDITY);
    else
        display.setWarningIcon(Display::Sensors::AIR_HUMIDITY,false);
}