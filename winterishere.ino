/**
* author: dekitarpg@gmail.com
* version: 1.0
* 
* This work is a derivative of 'DemoReel100' by 
* Mark Kriegsman from the FastLED examples library.
* - I mainly reworked the 'confetti' effect from 
* the example, for use with my own project. 
*/

#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

/**
* Define preprocessor constants
*/
#define DATA_PIN            3
//#define CLK_PIN           4
#define LED_TYPE            WS2812B
#define COLOR_ORDER         GRB
#define NUM_LEDS            45
#define BRIGHTNESS          172
#define FRAMES_PER_SECOND   30

/**
* Define global variables used.
*/
CRGB leds[NUM_LEDS];
bool gHueSwitching = false;
uint8_t gHue = 0;

/**
* Main Arduino setup() function
*/
void setup() {
  // 3 second delay for recovery
  delay(3000); 
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

/**
* Main Arduino loop() function
*/
void loop() {
  // uncomment the line for desired effect
  gameofthrones();
  //unicornrainbow();
  //imbatman();
  
  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 
}

/**
* gameofthrones() led effect function
*/
void gameofthrones(){
  // fadeout all leds
  fadeToBlackBy(leds, NUM_LEDS, 24);
  // get random led id
  int pos = random16(NUM_LEDS);
  // get maximum rand value based on sine wave
  int maxrand = beatsin8(30, 0, 64);
  // set the led id to hue value + rand(maxrand)
  leds[pos] = CHSV(gHue + random8(maxrand), 200, 255);
  // periodic update: 30 milliseconds
  EVERY_N_MILLISECONDS(30) { 
    // check if hue is switching
    if (gHueSwitching) {
      // increase global hue
      gHue++;
      // check if hue is any of desired values
      if (gHue == 0 || gHue == 132){
        // set hue switch flag to false
        gHueSwitching = false;
      }
    }
  }
  // periodic update: 15 seconds
  EVERY_N_SECONDS(15) { 
    // set hue switch flag to true
    gHueSwitching = true;
  } 
}

/**
* unicornrainbow() led effect function
*/
void unicornrainbow(){
  fill_rainbow(leds, NUM_LEDS, gHue, 7);
  byte chance = beatsin8(30, 0, 50);
  if( random8() < chance) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
  EVERY_N_MILLISECONDS(30) { 
    gHue++;
  }
}

/**
* imbatman() led effect function
*/
void imbatman() {
  fadeToBlackBy(leds, NUM_LEDS, 80);
  leds[beatsin16(10, 0, NUM_LEDS-1)] |= CHSV(0, 200, 255);
  leds[beatsin16(11, 0, NUM_LEDS-1)] |= CHSV(100, 200, 255);
  leds[beatsin16(12, 0, NUM_LEDS-1)] |= CHSV(140, 200, 255);
}

/**
* [End Of Code]
*/
