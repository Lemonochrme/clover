# 🍀 Clover > 💡 Embedded

## Synopsis

The use of modern C++ in embedded system is rather new and can be a little tricky to get used to it's philosophy and design. µControllers are little chips that have to work with efficient and optimized code, C++ is as fast as C, but can slower the processor when using idioms such as classes.

With the rise of fast chips and more advanced compiler techniques, C++ is now viable and widely spread among chips like the ESP32 we are using.

## Classes

Each classes in the Clover Embedded project has to have one goal. We do not need multiple classes that do the same thing. Each object in each folder has to be directly linked to the *"main"* class or should be an inheritance. 

### Component

Each Component is designed to communicate with a sensor/actuator. There is a main Component which is translated as an abstract class with basic functions. Each Component is derived from it and is used to do a more complex task.

The base Component uses an enumeration to know which data to send or receive, it uses the simple Arduino function to communicate with the external component. Some classes has to be created to use a given library for more complex communication.

| Derived Class  | Description                                                                           |
| -------------- | ------------------------------------------------------------------------------------- |
| `DHTComponent` | Communicate with the DHT sensor with the given `Adafruit_Sensor` and `DHT` libraries. |
| `LedComponent` | Communicate with the Chainable Led actuator with the given `ChainableLED` library.    |

The `MainComponent` is a singleton class that contains each component used for the project. it can be called anywhere.

### DataHandler

A Data container which converts a set of data into a ***JSON*** string vector. It can be updated on the main loop and is used to work directly with the `ServerHandler` class.

### Display

The Display folder is not considered as a sensor/actuator while using an external port. Because the complexity of the OLED screen is too wide, it has been made into its main directory. The Display Base Class ships with functions to show a certain screen.

| Screen Name  | Description                                                                                                                       | Type    |
| ------------ | --------------------------------------------------------------------------------------------------------------------------------- | ------- |
| Connecting   | With a given state (from 0 to 3), Will show a little "Connecting..." screen.                                                      | `Setup` |
| Connected    | With a given IP Address (gathered from ServerHandler) and a timing, will show the IP to the user and then fade to another screen. | `Setup` |
| Not Conncted | If no Wi-Fi found, will display an error message.                                                                                 | `Setup` |
| Boot         | Show the boot screen with each frame.                                                                                             |         |
| Loop         | The main Loop of the screen, shows information about sensors.                                                                     |         |

The Display uses a `Components` library which has been made to simplify the embedded code of the screen. The philosophy behind this class is the use of `Component` composed of multiple `Boxes` :

- `TextBox`: shows text, background and style customization, width and height, alignment in both y and x axes.

- `SpriteBox`: shows `.xbm` data, can be aligned in both y and x axes.

The `Component` is composed of the main abstract class `Box` and each type of Box can use these main functions :

| Function Name | Arguments                                                                           | Description                                                                    |
| ------------- | ----------------------------------------------------------------------------------- | ------------------------------------------------------------------------------ |
| Display       | `size`: total size of the element.`size_pos`: total size of the element above.      | Will call the OLED Library to draw pixels on the screen with the correct data. |
| Update        | `data`: Depending on the inheritance, will be *recasted* into text or picture data. | Will update the data of the `Box`.                                             |
| get...        | *None*                                                                              | Getters, used for inherited classes.                                           |
| SetOffset     | `xOffset`, `yOffset`                                                                | modify internal *x* and *y*.                                                   |

> ⚠️ Appending a `Box` inside `Component` would have no effect because the *Display()* function is blank.

Each Box can be fixed in x and y axis using the `StyleHeight` and `StyleWidth` enumerations. The philosophy is that each Box is placed depending on its Style. When adding another Box with the same style, the style counter will increase, hence, recalculating the position for both objects.

> ℹ️ The enumeration starting with `FORCE` will ignore this "restriction" and is placed like an absolute object.

Each Component can be displayed at the same time, so you can create independent object that still has a clear style in mind.

### Pictures

Pictures is not a class but rather a set of `.xbm` files for the Display.

> `.xbm` files are C-header with picture data (pixel-data, width, height), especially used for mono-color screens.

### ServerHandler

The Server Folder chips with the Wi-Fi and Web Server libraries from ESP, it will return status when connected, and communicates directly with the screen in the setup phase.

It has been designed to be a singleton, but is only used in the main loop. It uses the `LedComponent` to show the user the actual status of the connection.

When connected, simply join the IP given by the Display to gather the *JSON* data. *(Boot and setup has to be finished)*

## Singletons

The singleton paradigm is a creational design pattern that ensure that a class is only instanced once. It solves the never ending dependency between each class like in this example :

```cpp
class GameInput {
    // Game Input logic, functions, variables
}
```

> File GameInput.hpp

```cpp
#include "GameInput.hpp"

class Game {
    // Game logic, functions, variables
    private:
        GameInput& _input;
}
```

> File Game.hpp

```cpp
#include "GameInput.hpp"

class Character {
    // Game logic, functions, variables
    private:
        GameInput& _input;
}
```

> File Character.hpp

As you can see, each time the `GameInput` class has to be copied, or referenced as an object, and the problem with this basic method is that in a bigger project it can easily become a *dependency hell*.

Each Singleton Classes are created when the program starts and can be instanced around the program anywhere that the proper header is included. Even in `sources (.cpp)` files, which is ensure that a class is not dependent over another.

```cpp
class DataHandler {
public:
    // Singleton
    static DataHandler& GetInstance()
    {
        static DataHandler instance;
        return instance;
    }
private:
    // Singleton
    DataHandler();
    ~DataHandler();
    DataHandler(const DataHandler&) = delete;
    DataHandler& operator=(const DataHandler&) = delete;
```

> File [DataHandler.hpp](lib/DataHandler/DataHandler.hpp)

A singleton class has to have a private constructor and destructor. The copy operator `=` and constructor with a given object has to be removed, because it has to be called explicitly by reference. To call the object we can place it in a reference variable, or simply use the instance functions :

```cpp
DataHandler::GetInstance().doSomething();
// Or (be careful to use a reference)
auto& dataHandler = DataHandler::GetInstance();
dataHandler.doSomething();
```

## Environment file

⚠️ **Note :** The `.env` file should be written using exactly the given spelling. You should add both the `'` and `"`. Because the pre-compilation checks for a string to replace the Wi-Fi *SSID* and *password*

```
SSID_CLOVER='"SSID"'
PSWD_CLOVER='"PASSWORD"'
```