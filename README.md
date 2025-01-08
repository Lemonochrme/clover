# 🍀 Clover

🍀 Visit our [website](https://www.clover.ovh/) no longer active.

<img src="http://share.etheryo.fr/INSA/4096-3072-max.jpg" title="" alt="ds" data-align="center" max-width="500">

## 🍀 Purpose of the Project 🍀

The project aims to inform about the health of your little green friend. With the help of the Grove Kit sensors and an ESP32, each data can be acquired on your local network.

An OLED display gather the same information and can always show information in real-time. This screen displays the actual status of the Wi-Fi connection, with the help of  two colored LEDs.

Specifications of the project :

- Display showing connection status (success or failed)

- LED for hardware status (connection failed, no plant detected...)

- LED for plant status (soil too *wet*/*dry*, temperature too *high*/*low*)

- When booting successful, showing each data accordingly

- When entering the URL in the browser, showing JSON raw data

- Python built-in app to show status on any computer

- Support for two sensors : *Moisture Plant Sensor*, *Temperature & Humidity in the air*

### What could be added

- **In the *"near"* future** we will add support for a database of each species and inform the user of the plant's health based on this data.

- It would be interesting to have a system of software update. if we want to add support for other sensors, or fixes.

## 🔌 Components connections 🔌

| PINS          | Components                      | Type      |
| ------------- | ------------------------------- | --------- |
| `A0`          | Moisture Sensor v1.4            | `Analog`  |
| `D1` and `D2` | OLED Display 0.96'' *(SSD1315)* | `I2C`     |
| `D7` and `D8` | Chainable Leds v2.0             | `Digital` |
| `D3`          | Temperature&Humidity (*DHT11*)  | `Digital` |

## [💡 Embedded Programming Flow 💡](embedded)

Using the *platform IO* extension on *Visual Studio Code*, each object that will be linked with the main loop will be created in the [`lib`](embedded/lib/). Each Object should have a definite function and purpose, otherwise it should be labeled in a group.

To understand the embedded part you can read the [`README`](embedded) 

## [💻 Built-in Application 💻](app)

The built-in application is done in Python for Windows/Max/Linux based computers.

A web-app is available for both phones and computers, reachable via an URL provided by the Clover Application.

You can read more in the  [`README`](app)

## ❓ How to Install ❓

1. Simply install [*Visual Studio Code*](https://code.visualstudio.com/Download) or any app that supports [*PlatformIO*](https://platformio.org/). Then install this extension on your favorite IDE.

2. Write your Wi-Fi *SSID* and *password* in a created `.env` file inside the `embedded` directory.

3. Follow the guidelines on the components connections, flash the program and you are good to go !

*NB: If the screen is not detected, the program may not start.*
