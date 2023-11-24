#include <U8g2lib.h>
#include <Wire.h>

class Display {
    public:
        Display();
        void loop();
    private:
        U8G2_SSD1306_128X64_NONAME_F_HW_I2C* _display;
};