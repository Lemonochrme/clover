#include "Screen.hpp"
#include <vector>
#include <memory>

// XBM Files
#include "../Pictures/failed.xbm"

using namespace Display;

Screen::Screen() : _booted(0), _bootFrame(0)
{
  _screen = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE, SCL, SDA);
  _screen->begin();
  _width = _screen->getDisplayWidth();
  _height = _screen->getDisplayHeight();
  _loading = "";
}

Screen::~Screen()
{
}

void Screen::Setup(uint8_t *font)
{
  _font = font;
  _screen->setFont(_font);

  headerSetup = TextBox("Clover Setup", StyleWidth::LEFT, StyleHeight::TOP, U8G2_BTN_INV, 2, 5, true);
  // Static Components
  connectingWindow.Add({std::make_shared<TextBox>(headerSetup),
                        std::make_shared<TextBox>(TextBox("connect", StyleWidth::CENTERED, StyleHeight::CENTERED, U8G2_BTN_BW0))});
  connectionfailedWindow.Add({std::make_shared<TextBox>(headerSetup),
    std::make_shared<TextBox>(TextBox("Failed to connect.", StyleWidth::RIGHT, StyleHeight::CENTERED, U8G2_BTN_BW0,3)),
    std::make_shared<SpriteBox>(SpriteBox(failed_bits,failed_height,failed_width,StyleWidth::LEFT,StyleHeight::FORCE_CENTERED))});
  connectedWindow.Add({std::make_shared<TextBox>(headerSetup),
                       std::make_shared<TextBox>(TextBox("Connected to Wi-Fi !", StyleWidth::LEFT, StyleHeight::CENTERED, U8G2_BTN_BW0, 0, 2)),
                       std::make_shared<TextBox>(TextBox("IP address: ", StyleWidth::LEFT, StyleHeight::CENTERED, U8G2_BTN_BW0, 0, 2)),
                       std::make_shared<TextBox>(TextBox("addr", StyleWidth::CENTERED, StyleHeight::CENTERED, U8G2_BTN_BW0, 0, 2))});
  bootWindow.Add(std::make_shared<SpriteBox>(SpriteBox(clover_frames[0].data, clover_frames[0].height, clover_frames[0].width, StyleWidth::CENTERED, StyleHeight::CENTERED)));
  loopWindow.Add(std::make_shared<TextBox>(TextBox("Welcome to Clover!", StyleWidth::CENTERED, StyleHeight::CENTERED, U8G2_BTN_BW0, 0, 2)));
}

void Screen::connecting(uint8_t state)
{
  const size_t connectSize(16);
  char connectText[connectSize];

  // Connecting dot dot dot (depending on state)
  strncpy(connectText, "Connecting", connectSize);
  size_t currentLength = strlen(connectText);
  for (uint8_t i = 0; i < state; i++)
  {
    // Checking space
    if (currentLength + 1 < connectSize)
    {
      strncat(connectText, ".", currentLength + 1);
      currentLength += 1;
    }
  }

  _screen->clearBuffer();
  // Component
  connectingWindow.Update(1, String(connectText));
  connectingWindow.Display();
  // Displaying
  _screen->sendBuffer();
}

void Screen::notConnected()
{
  _screen->clearBuffer();
  // Component
  connectionfailedWindow.Display();
  // Displaying
  _screen->sendBuffer();
}

void Screen::connected(const char *ipaddress, uint8_t timing)
{
  _screen->clearBuffer();
  // Component
  connectedWindow.Update(3, String(ipaddress));

  // Displaying
  connectedWindow.Display();
  // Creating loading bar
  if (timing != 0)
  {
    _screen->setFont(u8g2_font_3x3basic_tr);
    _loading.concat(" ");
    _screen->drawButtonUTF8(0, _screen->getDisplayHeight() - 5, U8G2_BTN_INV, _screen->getStrWidth(_loading.c_str()), 0, 0, _loading.c_str());
    _screen->setFont(_font);
  }
  _screen->sendBuffer();
}

void Screen::boot()
{
  _screen->clearBuffer();
  // Component
  bootWindow.Display();
  _bootFrame++;
  bootWindow.Update(0,clover_frames[(_bootFrame >= 10 ? 10 : _bootFrame)]);
  _screen->sendBuffer();
}

void Screen::loop()
{
  _screen->clearBuffer();
  // Component
  loopWindow.Display();
  // Displaying
  _screen->sendBuffer();
}

uint16_t Screen::getHeight() { return _height; }
uint16_t Screen::getWidth() { return _width; }
U8G2_SSD1306_128X64_NONAME_F_HW_I2C &Screen::getScreen() { return *_screen; }
uint16_t Screen::getTextWidth(const char *str) { return _screen->getStrWidth(str); }
bool Screen::isBooting() { return (_bootFrame<=20); }