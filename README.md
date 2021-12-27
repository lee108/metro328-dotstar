# metro328-dotstar

This is a hello world project to get the Adafruit DotStart LED strip working with the METRO 328 board.

## Progress

DONE: Get Arduino IDE installed
* installed Arduino 1.8.19
* downloaded Silabs driver for the CP2104 USB to UART bridge and installed manually
[CP2104 Driver Link](https://www.silabs.com/documents/public/software/CP210x_Universal_Windows_Driver.zip)

DONE:Program Metro 328 with "Hello World"
* found Hello World example using the Serial library
[Hello World example](https://arduinogetstarted.com/tutorials/arduino-hello-world)
* setup baud to 9600 and printed one line in the setup function function

DONE: Wiggle some IOs
* found Hello LED example for setting a PIN and driving a blinking pattern
[Hello LED example](https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink)

DONE: Find Example Code or Drivers for DotStart LEDs
* soldered together the Proto-Screwshield
* found Arduino Library Installation guide for Adafruit DotStar LEDs
[DotStar\_Library Installation Guide](https://learn.adafruit.com/adafruit-dotstar-leds/arduino-library-installation) 

Done: Write to LEDs
* created metro-hello-dotstar project based off strand test example project
* note: operation was slow taking seconds to walk a led from start to end
* moved to dedicated spi pins accelerated the write operation significantly

Done: Create an interesting project that generates from fun patterns
* created separate fir filter for each color
* create function to draw bands like a coral snake
* initialized data to theamed stripes for Kai
* initialized fir filters with delayed impulse for crisp colors
* played with other schemes that blured pixels and propegated color at different rates
* ran into issues with rounding that causes some impluses to have a finit life

## Environment 
* Windows 10 laptop
* Gitbash
* Arduino IDE
   * Adafruit\_DotStar 1.1.5
* CP210x_Universial_Windows_Driver 11.0.0
## Hardware Setup
* Adafruit METRO 328         (PN:   50)
* Adafruit Proto-Screwshield (PN:  196)
* Adafruit Dotstar Led Strip (PN: 2240)
* Adafruit 5V 10A power brick(PN:  658)
