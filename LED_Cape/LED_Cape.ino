/*
 * Uses FastLED library:
 * https://github.com/FastLED/FastLED/archive/v3.1.0.zip
 * Extract zip contents to arduino sketchbook/libraries
*/
#include <FastLED.h>

#define LED_PIN     2
#define NUM_LEDS    110
#define BRIGHTNESS  70
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
int UPDATES_PER_SECOND = 100;
int timePerRoutine = 10000;

CRGB purple(41, 0, 41);
CRGB yellow(255, 149, 0);
CRGBPalette16 chasePallet = CRGBPalette16(
                                   purple, purple, purple, yellow,
                                   yellow, purple, purple, purple,
                                   yellow, yellow, purple, purple,
                                   purple, yellow, yellow, purple );
                                   
boolean primaryIsPurple = false;

void setup() {
  
    delay( 3000 );
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(BRIGHTNESS);
        
}


void loop(){
    
  chase(timePerRoutine);
  alternate(timePerRoutine);
    
}

//VISIBLE ROUTINES

void chase(int timeout){
  
  long start = millis();
  
  while((millis() - start) < timeout){
    
    UPDATES_PER_SECOND = 100;
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1;
    
    moveChase(startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    
  }
  
}

void alternate(int timeout){
  
  long start = millis();
  
  while((millis() - start) < timeout){
    
    UPDATES_PER_SECOND = 10;
  
    if(primaryIsPurple){
    
      yellowPrimary();
      primaryIsPurple = false;
    
    }else{
    
      purplePrimary();
      primaryIsPurple = true;
    
    }
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    
  }
  
}

//BACKEND FUNCTIONS

void moveChase(uint8_t colorIndex){
   
  uint8_t brightness = 255;
    
  for( int i = 0; i < NUM_LEDS; i++) {
      
      leds[i] = ColorFromPalette( chasePallet, colorIndex, brightness, LINEARBLEND);
      colorIndex += 3;
        
  }
    
}

void purplePrimary(){
  
  for(int i = 0; i < NUM_LEDS; i+=2){
    
    leds[i] = CRGB(41, 0, 41);
    
  }
  
  for(int i = 1; i < NUM_LEDS; i+=2){
    
    leds[i] = CRGB(255, 149, 0);
    
  }
  
}

void yellowPrimary(){
  
  for(int i = 1; i < NUM_LEDS; i+=2){
    
    leds[i] = purple;
    
  }
  
  for(int i = 0; i < NUM_LEDS; i+=2){
    
    leds[i] = CRGB(255, 149, 0);
    
  }
  
}
