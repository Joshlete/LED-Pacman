#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

/* chooses a random direction to move, except for backwards */
void random_direction(struct Dot *dot) {
  // choose random direction. make sure it's not reverse direction, unless it's only possible direction
  int dir = random(1,4);
  if(dot->bearing == UP) {
    if(check_direction(dot, LEFT) == false && check_direction(dot, UP) == false
    && check_direction(dot, RIGHT) == false) { dot->bearing = DOWN; }
    else {
      while(dir == DOWN) dir = random(1,4);
      dot->bearing = dir; 
    }
  } else if(dot->bearing == LEFT) {
    if(check_direction(dot, LEFT) == false && check_direction(dot, UP) == false
    && check_direction(dot, DOWN) == false) { dot->bearing = RIGHT; }
    else {
      while(dir == RIGHT) dir = random(1,4);
      dot->bearing = dir; 
    }
  } else if(dot->bearing == DOWN) {
    if(check_direction(dot, LEFT) == false && check_direction(dot, DOWN) == false
    && check_direction(dot, RIGHT) == false) { dot->bearing = UP; }
    else {
      while(dir == UP) dir = random(1,4);
      dot->bearing = dir; 
    }
  } else if(dot->bearing == RIGHT) {
    if(check_direction(dot, RIGHT) == false && check_direction(dot, UP) == false
    && check_direction(dot, RIGHT) == false) { dot->bearing = LEFT; }
    else {
      while(dir == LEFT) dir = random(1,4);
      dot->bearing = dir; 
    }
  } else { // dot has no movement, so initiate it
    while(!check_direction(dot, dir)) dir = random(1,4);
    dot->bearing = dir;
  }
}

/* check if dot can move in 'dir' direction                   *
 * returns true if 'dir' move is possible. else returns false */
bool check_direction(struct Dot *dot, int dir) {
  if(dir == UP) {
    if( leds[ mmap[dot->x][dot->y-1] ] != green) {
      // if user, they can't go into enemy area. SHOULD NOT NEED TO CHECK FOR USER BECAUSE OF ISR
      if(!dot->isEnemy && leds[ mmap[dot->x][dot->y-1] ] == enemyBaseColor) return false;
      return true;
    }
    else
      return false;
  } else if(dir == LEFT) {
    if( leds[ mmap[dot->x-1][dot->y] ] != green) {
      if(!dot->isEnemy && leds[ mmap[dot->x-1][dot->y] ] == enemyBaseColor) return false;
      return true;
    }
    else
      return false;
  } else if(dir == DOWN) {
    if( leds[ mmap[dot->x][dot->y+1] ] != green) {
      if(!dot->isEnemy && leds[ mmap[dot->x][dot->y+1] ] == enemyBaseColor) return false;
      return true;
    }
    else
      return false;
  } else if(dir == RIGHT) {
    if( leds[ mmap[dot->x+1][dot->y] ] != green) {
      if(!dot->isEnemy && leds[ mmap[dot->x+1][dot->y] ] == enemyBaseColor) return false;
      return true;
    }
    else
      return false;
  }
  return false;
}

/* checks if user inputted w, a, s, or d  *
 * returns 1 if true, 0 if false          */
int changeDirection(struct Dot *dot) {
  int wasPressed = 0;
  if(Serial.available() > 0) {
    int userInput = Serial.read();
    delay(10);

    // check if user pressed w,a,s,d
    if(userInput == 'w' && leds[ mmap[dot->x][pacman.y-1] ] != green) { // user wants to go up(w)
      dot->bearing = 1; 
      wasPressed = 1;
    }
    else if(userInput == 'a' && leds[ mmap[pacman.x-1][pacman.y] ] != green) { // user wants to go left(a)
      dot->bearing = 2; 
      wasPressed = 1;
    }
    else if(userInput == 's' && leds[ mmap[pacman.x][pacman.y+1] ] != green) { // user wants to go down(s)
      dot->bearing = 3; 
      wasPressed = 1;
    }
    else if(userInput == 'd' && leds[ mmap[pacman.x+1][pacman.y] ] != green) { // user wants to go right(d)
      dot->bearing = 4; 
      wasPressed = 1;
    } else if(userInput == 'q') { // user wants to stop. FOR DEBUGGING
      dot->bearing = 0; 
      if(debug) {
        Serial.print("User stopped at: (");
        Serial.print(pacman.x);
        Serial.print(", ");
        Serial.print(pacman.y);
        Serial.println(")");
      }
    } else if(userInput == 'r') {
      Serial.println("Game over!");
      delay(2000);
      resetFunc();
    }
  }
  return wasPressed;
}
 
/* moves dot in current direction its going. returns 1 if *
 * successully moved. returns 0 if failed                 */
int moveDot(struct Dot *dot) {
  int wasMoved = 0;
  
  if(dot->bearing == 1) { // move up
    // move dot up once
    if(leds[ mmap[dot->x][dot->y-1] ] != green) {
      // check if user's next spot has a white dot
      if(!dot->isEnemy && leds[ mmap[dot->x][dot->y-1] ] == white) {
        totalDots--;
        dot->background = black;
      }

      // replace current spot with what was under user
      leds[mmap[dot->x][dot->y]] = dot->background; // delete pacmans original spot
      dot->y--; // move users spot up
      leds[mmap[dot->x][dot->y]] = CRGB::Orange; // update pacmans new spot
      wasMoved = 1;
    } 
  } else if(dot->bearing == 2) { // move left
    if(leds[ mmap[dot->x-1][dot->y] ] != green
    && leds[ mmap[dot->x-1][dot->y] ] != enemyBaseColor
    && leds[ mmap[dot->x-1][dot->y] ] != blue) {
      if(leds[ mmap[dot->x-1][dot->y] ] == white) {
        totalDots--;
        Serial.print("Total dots: ");
        Serial.println(totalDots);
      }
      leds[mmap[dot->x][dot->y]] = black;
      dot->x--;
      leds[mmap[dot->x][dot->y]] = CRGB::Orange;
      wasMoved = 1;
    }
    
  } else if(dot->bearing == 3) { // move down
    if(leds[ mmap[dot->x][dot->y+1] ] != green
    && leds[ mmap[dot->x][dot->y+1] ] != enemyBaseColor
    && leds[ mmap[dot->x][dot->y+1] ] != blue) {
      if(leds[ mmap[dot->x][dot->y+1] ] == white) {
        totalDots--;
        Serial.print("Total dots: ");
        Serial.println(totalDots);
      }
      leds[mmap[dot->x][dot->y]] = black;
      dot->y++;
      leds[mmap[dot->x][dot->y]] = CRGB::Orange;
      wasMoved = 1;
    }

  } else if(dot->bearing == 4) { // move right
    if(leds[ mmap[dot->x+1][dot->y] ] != green
    && leds[ mmap[dot->x+1][dot->y] ] != enemyBaseColor
    && leds[ mmap[dot->x+1][dot->y] ] != blue) {
      if(leds[ mmap[dot->x+1][dot->y] ] == white) {
        totalDots--;
        Serial.print("Total dots: ");
        Serial.println(totalDots);
      }
      leds[mmap[dot->x][dot->y]] = black;
      dot->x++;
      leds[mmap[dot->x][dot->y]] = CRGB::Orange;
      wasMoved = 1;
    }
    
  }
  FastLED.show();
  delay(DOT_SPEED);
  return wasMoved;
}

/* ISR's for up, left, down, right movement from buttons      *
 * ISR will only activate when button goes from HIGH to LOW,  *
 * or unpressed to pressed. continuous hold of button will    *
 * not activate ISR.                                          */
void button_up_ISR() {
  if(leds[ mmap[pacman.x][pacman.y-1] ] != green
  && leds[ mmap[pacman.x][pacman.y-1] ] != enemyBaseColor
  && leds[ mmap[pacman.x][pacman.y-1] ] != blue) {
    pacman.bearing = 1;
  }
}

void button_left_ISR() {
  if(leds[ mmap[pacman.x-1][pacman.y] ] != green
  && leds[ mmap[pacman.x-1][pacman.y] ] != enemyBaseColor
  && leds[ mmap[pacman.x-1][pacman.y] ] != blue) {
    pacman.bearing = 2;
  }
}

void button_down_ISR() {
  if(leds[ mmap[pacman.x][pacman.y+1] ] != green
  && leds[ mmap[pacman.x][pacman.y+1] ] != enemyBaseColor
  && leds[ mmap[pacman.x][pacman.y+1] ] != blue) {
    pacman.bearing = 3;
  }
}

void button_right_ISR() {
  if(leds[ mmap[pacman.x+1][pacman.y] ] != green
  && leds[ mmap[pacman.x+1][pacman.y] ] != enemyBaseColor
  && leds[ mmap[pacman.x+1][pacman.y] ] != blue) {
    pacman.bearing = 4;
  }
}
