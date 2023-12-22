#ifndef _HEADER_COMPONENT_MAIN
#define _HEADER_COMPONENT_MAIN

#include "Component.hpp"
#include "LedComponent.hpp"
#include "DHTComponent.hpp"

class MainComponent {
public:
    // Singleton
    static MainComponent& GetInstance()
    {
        static MainComponent instance;
        return instance;
    }
    // Public functions
    void setup();
    Component& getHumidity();
    LedComponent& getLed();
    DHTComponent& getDHT();
private:
    // Singleton
    MainComponent();
    ~MainComponent();
    MainComponent(const MainComponent&) = delete;
    MainComponent& operator=(const MainComponent&) = delete;
    
    // Components
    Component _humidity;
    LedComponent _led;
    DHTComponent _dht;
};

#endif //