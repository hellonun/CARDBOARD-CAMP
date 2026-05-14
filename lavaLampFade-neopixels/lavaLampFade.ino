// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is' connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN 12

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 5

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();             // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();              // Turn OFF all pixels ASAP
  strip.setBrightness(50);  // Set BRIGHTNESS to about 1/5 (max = 255)
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  // Fill along the length of the strip in various colors...
  // colorWipe(strip.Color(255,   0,   0), 255); // Red
  // colorWipe(strip.Color(  0, 255,   0), 255); // Green
  // colorWipe(strip.Color(  0,   0, 255), 255); // Blue

  // // Do a theater marquee effect in various colors...
  // theaterChase(strip.Color(127, 127, 127), 255); // White, half brightness
  // theaterChase(strip.Color(127,   0,   0), 255); // Red, half brightness
  // theaterChase(strip.Color(  0,   0, 127), 255); // Blue, half brightness


  blueOrangeFade(5);

  // rainbow(10);             // Flowing rainbow cycle along the whole strip
  // theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
}


void blueOrangeFade(int wait) {
  // Fade from blue to white
  for(int i = 0; i <= 255; i++) {
    uint8_t r = i;
    uint8_t g = i;
    uint8_t b = 255;
    for(int p = 0; p < strip.numPixels(); p++)
      strip.setPixelColor(p, strip.Color(r, g, b));
    strip.show();
    delay(wait);
  }

  // Fade from white to orange
  for(int i = 0; i <= 255; i++) {
    uint8_t r = 255;
    uint8_t g = 255 - (175 * i) / 255;  // 255 -> 80
    uint8_t b = 255 - i;                 // 255 -> 0
    for(int p = 0; p < strip.numPixels(); p++)
      strip.setPixelColor(p, strip.Color(r, g, b));
    strip.show();
    delay(wait);
  }

  // Pause at orange
  delay(1000);

  // Fade from orange to white
  for(int i = 0; i <= 255; i++) {
    uint8_t r = 255;
    uint8_t g = 80 + (175 * i) / 255;   // 80  -> 255
    uint8_t b = i;                        // 0   -> 255
    for(int p = 0; p < strip.numPixels(); p++)
      strip.setPixelColor(p, strip.Color(r, g, b));
    strip.show();
    delay(wait);
  }

  // Fade from white to blue
  for(int i = 0; i <= 255; i++) {
    uint8_t r = 255 - i;                 // 255 -> 0
    uint8_t g = 255 - i;                 // 255 -> 0
    uint8_t b = 255;
    for(int p = 0; p < strip.numPixels(); p++)
      strip.setPixelColor(p, strip.Color(r, g, b));
    strip.show();
    delay(wait);
  }

  // Pause at blue
  delay(1000);
}
