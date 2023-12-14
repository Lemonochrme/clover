#ifndef _HEADER_COMPONENT_DHT
#define _HEADER_COMPONENT_DHT
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

class DHTComponent
{
public:
    DHTComponent(uint8_t type, byte pin);
    ~DHTComponent();
    void setup();
    float getHumidity();
    float getTemperature();

private:
    byte _pin;
    uint8_t _type;
    DHT_Unified* _dht;
    sensors_event_t _event;
};

#endif // _HEADER_COMPONENT_LED