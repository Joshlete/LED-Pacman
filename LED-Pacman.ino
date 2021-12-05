#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <FastLED.h>
#include <LinkedList.h>

/* DEFINES */
#define DATA_PIN    8
#define NUM_LEDS    288
#define NUM_ROWS    17
#define NUM_COLS    17
#define BRIGHTNESS  30
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define DOT_SPEED 100

/* STRUCTURES */
struct Dot {
  int x, y;
} food, pacman, tempDot;

/* GLOBAL VARIABLES */
CRGB leds[NUM_LEDS];
int mmap[NUM_ROWS][NUM_COLS] = {};
int userInput = 0;
int dir = 0; // 1 = up, 2 = left, 3 = down, 4 = right
int debug = 1;

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(9600);

  // create 2d array of LED lights. j = x, i = y
  // each value holds location of LED on strip 
  int curLED = -1; // first light is a phantom light, so start at -1
  for(int i = 16; i >= 0; i--) {
    for(int j = 16; j >= 0; j--) {
      mmap[j][i] = curLED;
      curLED++;
    }

    // decrease curLED and increment to get next row
    // if total rows are odd, make sure the last row(decrementing)
    // down is checked
    if(i >= 1) {
      i--; // going to next row up
      for(int j = 0; j <= 16; j++) {
        mmap[j][i] = curLED;
        curLED++;
      }
    }
  }

  // initialize border
  for(int i = 0; i <= 16; i++) {
    leds[mmap[0][i]] = CRGB::Blue; // left
    leds[mmap[i][0]] = CRGB::Blue; // top
    leds[mmap[16][i]] = CRGB::Blue; // right
    leds[mmap[i][16]] = CRGB::Blue; // bottom
  }

  // initialize pacman
  leds[mmap[8][8]] = CRGB::Orange;
  pacman.x = 8; pacman.y = 8;
  

  FastLED.show();
}

void loop() {
  // check if user pressed w,a,s,d key
  changeDirection();

  // move user in direction it's going
  moveUser();
  
}

/* resets program */
void(* resetFunc) (void) = 0; // declare reset function at address 0
