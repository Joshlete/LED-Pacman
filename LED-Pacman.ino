#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <FastLED.h>

/* DEFINES */
#define DATA_PIN    8
#define NUM_LEDS    288
#define NUM_ROWS    17
#define NUM_COLS    17
#define BRIGHTNESS  15
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define DOT_SPEED 200 // higher number == slower speed


/********* STRUCTURES ***************
 *  enemy1 = move around randomly   *
 *  enemy2 = dijkstras algorithm    *
 *  to-do: add color var to Dot,    *
 *         enemy2,                  *
 ************************************/
struct Dot {
  int x, y, bearing;
  bool isEnemy;
  CHSV background, color;
} pacman, enemy1;

/* GLOBAL VARIABLES */
CRGB leds[NUM_LEDS];
CRGB yellow = CRGB::Orange;
CRGB blue = CRGB::DarkBlue;
CHSV black(0, 0, 0);
//CRGB black = CRGB::Black;
CHSV green(85, 255, 200);
CHSV white(CRGB::White, 25, 120);
CHSV enemyBaseColor(85, 100, 120);
int mmap[NUM_ROWS][NUM_COLS] = {};
int userInput = 0;
int debug = 1;
int totalDots = 1;
struct Dot enemyBase1[3] = {};

/* button pin numbers */
const int BUTTON_UP = 2;
const int BUTTON_LEFT = 3;
const int BUTTON_DOWN = 18;
const int BUTTON_RIGHT = 19;



void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(9600);
  randomSeed(analogRead(0));

  //initialize buttons
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);

  // Initialize ISR's for buttons
  attachInterrupt(digitalPinToInterrupt(BUTTON_UP), button_up_ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_LEFT), button_left_ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_DOWN), button_down_ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_RIGHT), button_right_ISR, FALLING);

  // setup 2d array of light strip
  // MAKE THIS MORE DYNAMIC
  detectMap();

  // set up map1
  initializeMapLayout();

  // add all the white dots
  fillMapWithDots();
  
  // initialize pacman
  initialize_dot(&pacman, 8, 9, 0, false, yellow, black); 
  leds[mmap[8][9]] = yellow;
  
  // initialize enemies
  initialize_dot(&enemy1, 8, 7, 0, true, blue, enemyBaseColor);
  leds[mmap[8][7]] = blue;

  
  

  FastLED.show();
}

void loop() {
  // check if user pressed w,a,s,d key
  // changeDirection(&pacman);

  // move user in direction it's going
  moveDot(&pacman);

  // move enemy1
  random_direction(&enemy1);
  //moveDot(&enemy1);

  
  
}

/* sets up dot for setup with all the data it needs *
 *  
 */
void initialize_dot(struct Dot *dot, int x, int y, int dir, bool enemy, CHSV colorr, CHSV backgroundd) {
  dot->x = x; dot->y = y; dot->bearing = dir; dot->isEnemy = enemy; dot->color = colorr; dot->background = backgroundd;
}

/* resets program */
void(* resetFunc) (void) = 0; // declare reset function at address 0
