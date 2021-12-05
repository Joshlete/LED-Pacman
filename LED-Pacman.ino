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
#define DOT_SPEED 200 // higher number == slower speed

/* STRUCTURES */
struct Dot {
  int x, y;
} food, pacman, tempDot;

/* GLOBAL VARIABLES */
CRGB leds[NUM_LEDS];
CRGB yellow = CRGB::Orange;
CRGB blue = CRGB::DarkBlue;
CRGB black = CRGB::Black;
CRGB white = CRGB::White;
CRGB green = CRGB::Green;
int mmap[NUM_ROWS][NUM_COLS] = {};
int userInput = 0;
int dir = 0; // 1 = up, 2 = left, 3 = down, 4 = right
int debug = 1;
int totalDots = 0;


void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(9600);

  // setup 2d array of light strip
  detectMap();

  // 
  initializeMapLayout();

  // initialize pacman
  pacman.x = 8; pacman.y = 9;
  leds[mmap[8][9]] = CRGB::Orange;

  // add all the white dots
  fillMapWithDots();
  
  

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
