#include "Display.hpp"

Display::Display()
{
    _display = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0,U8X8_PIN_NONE,SCL,SDA);
    _display->begin();
}

void Display::loop()
{
  _display->clearBuffer();                   // clear the internal memory
  _display->setFont(u8g2_font_ncenB08_tr);   // choose a suitable font
  _display->drawStr(0,10,"Hello World!");    // write something to the internal memory
  _display->sendBuffer();                    // transfer internal memory to the display
  delay(1000); 
}