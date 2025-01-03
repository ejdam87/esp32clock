# ESP32-driven clock device

This repository contains source code for a simple clock device controlled by ESP32 microcontroller.

## Appearance

| Front | Back |
|----------|----------|
|   ![front](./ims/front.jpg)   |   ![back](./ims/back.jpg)   |

## Hardware

-   ESP32 microcontroller
-   Jumper wires
-   MG90S servo motor
-   MAX7219 LED display (32 x 8)
-   MB102 power supply module
-   Power bank

Besides that, I mounted a small plastic sand-glass to the servo motor.

## Software

I assume existance of file `credentials.h` which stores SSID and password for WiFi connection.
Files `display.cpp` and `display.h` contain extension of [MAX7219 driver](https://docs.arduino.cc/libraries/ledcontrol/) providing simple interface for individual LED manipulation.
Finally, `clock.ino` contains all the instructions for controlling display and servo motor. It uses [ESP32 servo library](https://docs.arduino.cc/libraries/esp32servo/) for motor control.
