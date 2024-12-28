#include <LedControl.h>

class ExtendedDisplay : LedControl
{

public:

  ExtendedDisplay(int data, int clock, int cs, int devices);
  void setIntensity(int intensity);
  void shutdown(bool status);
  void clearDisplay();
  void setLed(int row, int column, bool state);

};
