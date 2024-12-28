#include "display.h"
#include "credentials.h"

#include "WiFi.h"
#include <time.h>
#include <SPI.h>

// Pin definitions for MAX7219
const int DIN_PIN = 23;  // Data In
const int CS_PIN = 5;   // Chip Select
const int CLK_PIN = 18;  // Clock

const int WIDTH = 8 * 4;
const int HEIGHT = 8;
const int DIGIT_WIDTH = 4;

const char* TIMEZONE = "CET-1CEST,M3.5.0/02:00:00,M10.5.0/03:00:00";
const char* NTP_SERVER = "pool.ntp.org";

// Initialize the LedControl library
// Parameters: DataIn, Clock, Load(CS), Number of MAX7219 devices
ExtendedDisplay display = ExtendedDisplay(DIN_PIN, CLK_PIN, CS_PIN, 4);

void putDigit( int digit, int segment )
{
  int offset = 2 + segment * HEIGHT;
  int rows[4] = {0, 2, 5, 7};
  for ( int i = 0; i < 4; i++ ) // single decimal digit can be represented with 4 bits
  {
    int bin = digit % 2;
    bool state = bin == 1 ? true : false;
    for ( int j = 0; j < DIGIT_WIDTH; j++ )
    {
      display.setLed( rows[i], offset + j, state );
    }

    digit >>= 1;
  }
}

void showTime( struct tm* time_info )
{
  int hours = time_info -> tm_hour;
  int minutes = time_info -> tm_min;

  putDigit( hours % 10, 1 );
  hours /= 10;
  putDigit( hours % 10, 0 );

  putDigit( minutes % 10, 3 );
  minutes /= 10;
  putDigit( minutes % 10, 2 );
}

void setup()
{
  // Initialize serial communication
  Serial.begin( 115200 );

  // Initialize the MAX7219 device
  display.shutdown( false );       // Wake up the MAX7219 from power-saving mode
  display.setIntensity( 8 );       // Set brightness level (0 is min, 15 is max)
  display.clearDisplay();          // Clear the display

  // Connect to Wi-Fi
  WiFi.begin( SSID, WIFI_PASSWORD );
  while ( WiFi.status() != WL_CONNECTED )
  {
    delay( 1000 );
    Serial.println( "Connecting to WiFi..." );
  }

  // Synchronize time
  configTzTime(TIMEZONE, NTP_SERVER);
  delay( 5000 );  // wait for response

  WiFi.disconnect();
  WiFi.mode( WIFI_OFF );

}

void loop()
{
  struct tm time_info = { 0 };
  time_t now = { 0 };
  time( &now );
  localtime_r( &now, &time_info );
  showTime( &time_info );

  delay( 1000 );
}
