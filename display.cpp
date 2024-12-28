#include "display.h"

const int DEVICE_SIZE = 8;

ExtendedDisplay::ExtendedDisplay(int data, int clock, int cs, int devices) : LedControl(data, clock, cs, devices) {}

void ExtendedDisplay::setIntensity(int intensity)
{
  for (int i = 0; i < getDeviceCount(); i++)
  {
    LedControl::setIntensity(i, intensity);
  }
}

void ExtendedDisplay::shutdown(bool status)
{
  for (int i = 0; i < getDeviceCount(); i++)
  {
    LedControl::shutdown(i, status);
  }
}

void ExtendedDisplay::clearDisplay()
{
  for (int i = 0; i < getDeviceCount(); i++)
  {
    LedControl::clearDisplay(i);
  }
}

void ExtendedDisplay::setLed(int row, int col, bool state)
{
  LedControl::setLed(col / DEVICE_SIZE, row, (DEVICE_SIZE - 1) - col % DEVICE_SIZE, state);
}
