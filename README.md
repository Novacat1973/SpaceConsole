# SpaceConsole
This is a small project of a space console for kids to play with.

It uses an **Arduino Nano** to control a set of **18 WS2811 RGB LEDs**. The LEDs are manipulated through **two push buttons** and **two 10kΩ potentiometers**, allowing dynamic adjustment of brightness, speed, mode, and color.  

## Features

- **Brightness Control**:  
  Adjust the brightness of the LEDs using **Potentiometer 1**.
  
- **Speed Control**:  
  Modify the speed of animations using **Potentiometer 2**.
  
- **LED Modes**:  
  Switch between the following modes using **Button 1**:
  - **Constant Color**: LEDs display a steady color.
  - **Blinking**: LEDs blink at the specified speed.
  - **Chase/Lauflicht**: LEDs light up sequentially like a running light.

- **Color Options**:  
  Change colors using **Button 2**:
  - **White**, **Red**, **Green**, **Blue**.
  - **Rainbow/Automatic RGB Color Cycle**.

## Hardware Requirements

- **Arduino Nano** (or compatible)
- **18 WS2811 RGB LEDs** + holders
- **2 Push Buttons**
- **2 Linear Potentiometers (10kΩ)**
- **External 5V Power Supply** (capable of providing at least 2A)

## Software Requirements

- **Arduino IDE** (version 1.8.19 or newer)
- **FastLED Library** (Install from Arduino Library Manager)

## License

This project is licensed under the [MIT License](LICENSE).

## Credits

- **FastLED Library**: [GitHub](https://github.com/FastLED/FastLED)
- Circuit and code designed by *Novacat1973*.
