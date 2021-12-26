#include <Adafruit_DotStar.h>
#include <SPI.h>

#define PIX_PER_M  60
#define M_IN_STRIP 4
#define NUMPIXELS  PIX_PER_M * M_IN_STRIP
#define DATAPIN    11
#define CLOCKPIN   13

Adafruit_DotStar strip(NUMPIXELS, DOTSTAR_BRG);

void setup() {
  // put your setup code here, to run once:

  // initialize the UART to operate at 9600 BAUD
  Serial.begin(9600);
  Serial.println("Serial Port: Inialized for 9600 BAUD");

  // initialize Dotstar
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
  Serial.println("DotStar LEDs: Inialized");
  
}

void loop() {
  // put your main code here, to run repeatedly

  static int head = 0;
  static int tail = -1;
  static uint32_t color = 0xFF0000;

  strip.setPixelColor(head, color); // 'On' pixel at head
  strip.setPixelColor(tail, 0);     // 'Off' pixel at tail
  strip.show();                     // Refresh strip
  delay(5);                        // Pause 20 milliseconds (~50 FPS)

  if(++head >= NUMPIXELS) {
    head = 0;
    if((color >>= 9) == 0){
     color = 0xFF0000;
    }
  }
  if(++tail >= NUMPIXELS) tail = 0;
}
