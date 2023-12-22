#ifndef _HEADER_COMPONENT_DHT
#define _HEADER_COMPONENT_DHT
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

class DHTComponent
{
public:
    /**
     * @brief Construct a new DHTComponent object
     * 
     * @param type type of DHT given by the DHT_U.h
     * @param pin the pin where the DHT is connected
     */
    DHTComponent(uint8_t type, byte pin);
    ~DHTComponent();

    /**
     * @brief called once the setup() is done in Arduino
     */
    void setup();

    /**
     * @brief Get the Humidity value
     * 
     * @return float from 0.0 to 100.0%
     */
    float getHumidity();

    /**
     * @brief Get the Temperature value
     * 
     * @return float in Celcius
     */
    float getTemperature();

private:
    byte _pin;
    uint8_t _type;
    DHT_Unified* _dht;
    sensors_event_t _event;
};

#endif // _HEADER_COMPONENT_LED