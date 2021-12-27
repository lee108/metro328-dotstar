#include <Adafruit_DotStar.h>
#include <SPI.h>

//
// Stript Parameters
//
#define PIX_PER_M  60
#define M_IN_STRIP 4
#define NUMPIXELS  PIX_PER_M * M_IN_STRIP
#define DATAPIN    11
#define CLOCKPIN   13

//
// FIR filter Parameters
//
#define FIR_N      5
#define NUM_COLORS 3

//
// FIR Filter Variables
//

// color order G R B
// set group delay and bluring function
uint16_t  h[NUM_COLORS][FIR_N] = {{0,256, 0, 0,0},{0,256, 0,0,0},{0,256, 0,0,0}};

// local filter history
uint8_t   x[NUM_COLORS][FIR_N];

Adafruit_DotStar strip(NUMPIXELS, DOTSTAR_BRG);

void drawBands(int offset, uint32_t primaryColor, int primaryBandWidth, uint32_t accentColor, int accentBandWidth);

void setup() {
  // put your setup code here, to run once:

  // initialize the UART to operate at 9600 BAUD
  Serial.begin(9600);
  Serial.println("Serial Port: Inialized for 9600 BAUD");

  // initialize Dotstar
  strip.begin(); // Initialize pins for output

  // create Hogwarts House Colors for Kai
  strip.fill(0x202020,  0, NUMPIXELS); // set default to white

  int primaryBandWidth = 5;
  int accentBandWidth = 1;

  // Hufflepuff
  drawBands(0, 0xffff00, primaryBandWidth, 0x000000, accentBandWidth);
  
  // Slytherin
  drawBands(20, 0xff0000, primaryBandWidth, 0x010101, accentBandWidth);

  // Griffendor
  drawBands(40, 0x00ff00, primaryBandWidth, 0xffff00, accentBandWidth);
  
  // Ravenclaw
  drawBands(60, 0x0000ff, primaryBandWidth, 0x010101, accentBandWidth);

  strip.show();  // Turn all LEDs off ASAP
  Serial.println("DotStar LEDs: Inialized");

  // initialize FIR filter
  // for each color
  for(int k=0; k < NUM_COLORS; k++){
    for(int j=0; j > FIR_N; j++){
      x[k][j] = (strip.getPixelColor(NUMPIXELS-j-1) >> k*8) & 0xFF;
    }
  }
  Serial.println("FIR filter: Inialized");
}

void loop() {
  // put your main code here, to run repeatedly
  uint32_t accum;
  uint32_t rgb;
  
  // for each pixel "i"
  for(int i=0; i < NUMPIXELS; i++){
  
    // for each color channel "k"
    rgb = 0;
    for(int k=0; k<NUM_COLORS; k++){
    
      // update local histor of last output
      for(int j=FIR_N-1; j > 0; j--){
           x[k][j] = x[k][j-1];
      }
      x[k][0] = (strip.getPixelColor(i) >> k*8) & 0xFF;
      
      // apply FIR filter impluse response h[k][n]
      accum = 0;
      for(int j=0; j < FIR_N; j++){
         accum += x[k][j]*h[k][j];
      }
      accum = (accum + (1 << 7)) >> 8;

      //truncate value if there is overflow to stop channel bleed
      accum &= 0xFF;

      // splice color back into a single word
      rgb |= accum << k*8;    
    } // for each color

     strip.setPixelColor(i,rgb);
  
  } // for each pixel
  strip.show();                     // Refresh strip
  delay(10);                        // Pause 20 milliseconds (~50 FPS)

}

void drawBands(int offset, uint32_t primaryColor, int primaryBandWidth, uint32_t accentColor, int accentBandWidth){
  strip.fill(accentColor ,   offset,  accentBandWidth);
  offset += accentBandWidth;
  strip.fill(primaryColor,   offset,  primaryBandWidth);
  offset += primaryBandWidth;
  strip.fill(accentColor ,   offset,  accentBandWidth);
}
