/* checks if user inputted w, a, s, or d  *
 * returns 1 if true, 0 if false          */
int changeDirection() {
  int wasPressed = 0;
  if(Serial.available() > 0) {
    userInput = Serial.read();

    // check if user pressed w,a,s,d
    if(userInput == 'w' && leds[ mmap[pacman.x][pacman.y-1] ] != green) { // user wants to go up(w)
      dir = 1; 
      wasPressed = 1;
    }
    else if(userInput == 'a' && leds[ mmap[pacman.x-1][pacman.y] ] != green) { // user wants to go left(a)
      dir = 2; 
      wasPressed = 1;
    }
    else if(userInput == 's' && leds[ mmap[pacman.x][pacman.y+1] ] != green) { // user wants to go down(s)
      dir = 3; 
      wasPressed = 1;
    }
    else if(userInput == 'd' && leds[ mmap[pacman.x+1][pacman.y] ] != green) { // user wants to go right(d)
      dir = 4; 
      wasPressed = 1;
    } else if(userInput == 'q') { // user wants to stop. FOR DEBUGGING
      dir = 0; 
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
 
/* moves food in current direction its going. returns 1 if  *
 * successully moved. returns 0 if failed                   */
int moveUser() {
  // move in direction it currently going
  int wasMoved = 0;
  if(dir == 1) { // move up
    // move pacman up once
    if(leds[ mmap[pacman.x][pacman.y-1] ] != green) { // touched border
      if(leds[ mmap[pacman.x][pacman.y-1] ] == whitee) {
        totalDots--;
        Serial.print("Total dots: ");
        Serial.println(totalDots);
      }
      leds[mmap[pacman.x][pacman.y]] = CRGB::Black; // delete pacmans original spot
      pacman.y--; // move pacmans spot up
      leds[mmap[pacman.x][pacman.y]] = CRGB::Orange; // update pacmans new spot
      wasMoved = 1;
    } 
  } else if(dir == 2) { // move left
    if(leds[ mmap[pacman.x-1][pacman.y] ] != green) {
      if(leds[ mmap[pacman.x-1][pacman.y] ] == whitee) {
        totalDots--;
        Serial.print("Total dots: ");
        Serial.println(totalDots);
      }
      leds[mmap[pacman.x][pacman.y]] = CRGB::Black;
      pacman.x--;
      leds[mmap[pacman.x][pacman.y]] = CRGB::Orange;
      wasMoved = 1;
    }
    
  } else if(dir == 3) { // move down
    if(leds[ mmap[pacman.x][pacman.y+1] ] != green) {
      if(leds[ mmap[pacman.x][pacman.y+1] ] == whitee) {
        totalDots--;
        Serial.print("Total dots: ");
        Serial.println(totalDots);
      }
      leds[mmap[pacman.x][pacman.y]] = CRGB::Black;
      pacman.y++;
      leds[mmap[pacman.x][pacman.y]] = CRGB::Orange;
      wasMoved = 1;
    }

  } else if(dir == 4) { // move right
    if(leds[ mmap[pacman.x+1][pacman.y] ] != green) {
      if(leds[ mmap[pacman.x+1][pacman.y] ] == whitee) {
        totalDots--;
        Serial.print("Total dots: ");
        Serial.println(totalDots);
      }
      leds[mmap[pacman.x][pacman.y]] = CRGB::Black;
      pacman.x++;
      leds[mmap[pacman.x][pacman.y]] = CRGB::Orange;
      wasMoved = 1;
    }
    
  }
  FastLED.show();
  delay(DOT_SPEED);
  return wasMoved;
}
