#include "Screen.hpp"
#include <string.h>
#include <vector>

using namespace Display;

Screen::Screen()
{
  _screen = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE, SCL, SDA);
  _screen->begin();
  _width = _screen->getDisplayWidth();
  _height = _screen->getDisplayHeight();
}

Screen::~Screen()
{
}

void Screen::Setup(uint8_t *font)
{
  _font = font;
  _screen->setFont(_font);

    // Static Components
  connectingWindow.Add(TextBox("connect",StyleWidth::CENTERED, U8G2_BTN_BW0));
  connectedWindow.Add({TextBox("Connected to Wi-Fi !", StyleWidth::LEFT, U8G2_BTN_BW0),
                       TextBox("IP address: ", StyleWidth::LEFT, U8G2_BTN_BW0),
                       TextBox("addr", StyleWidth::CENTERED, U8G2_BTN_BW0)});
}

uint16_t Screen::setupHeader(const uint16_t w_padding, const uint16_t h_padding)
{
  _screen->setFont(u8g2_font_helvB08_tr);
  // calculating y position
  const uint16_t y = FONT_SIZE + ((w_padding + 1) * 2);
  _screen->drawButtonUTF8(w_padding, y, U8G2_BTN_INV, _screen->getDisplayWidth(), h_padding, w_padding, "Clover Setup");
  return y;
}

void Screen::connecting(uint8_t state)
{
  const size_t connectSize(16);
  char connectText[connectSize];

  // Connecting dot dot dot (depending on state)
  strncpy(connectText, "Connecting", connectSize);
  for (uint8_t i = 0; i < state; i++)
    strncat(connectText, ".", connectSize);

  // Displaying connecting text and setup bar.
  _screen->clearBuffer();
  const auto setupPadding = setupHeader();

  // Reactive Component
  connectingWindow.Update(0,connectText);
  // Displaying
  connectingWindow.Display(StyleHeight::CENTERED, setupPadding);
  _screen->sendBuffer();
}

void Screen::connected(const char *ipaddress)
{
  // Displaying connecting text and setup bar.
  _screen->clearBuffer();
  const auto setupPadding = setupHeader();

  // Reactive Component
  connectedWindow.Update(2,ipaddress);
  // Displaying
  connectedWindow.Display(StyleHeight::CENTERED, setupPadding+5);
  _screen->sendBuffer();
}

void Screen::loop()
{
  _screen->clearBuffer(); // clear the internal memory
  _screen->setFont(_font);
  _screen->drawStr(0, 10, "Hello World!"); // write something to the internal memory
  _screen->sendBuffer();                   // transfer internal memory to the display
  delay(1000);
}

uint16_t Screen::getHeight() { return _height; }
uint16_t Screen::getWidth() { return _width; }
U8G2_SSD1306_128X64_NONAME_F_HW_I2C &Screen::getScreen() { return *_screen; }
uint16_t Screen::getTextWidth(const char *str) { return _screen->getStrWidth(str); }