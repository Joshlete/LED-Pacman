/* creates a 2d array of a lightstrip
 * going left to right, right to left, and so on..
 */

void detectMap() {
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

}

void fillMapWithDots() {
  for(int i = 16; i >= 0; i--) {
    for(int j = 16; j >= 0; j--) {
        if(leds[ mmap[i][j] ] == black) {
          leds[ mmap[i][j] ] = CHSV(white, 50, 120);
          totalDots++;
        }
    }
  }
  
}

/* sets up a map with a specific layout */
void initializeMapLayout() {
  // initialize border
  for(int i = 0; i <= 16; i++) {
    leds[mmap[0][i]] = green; // left
    leds[mmap[i][0]] = green; // top
    leds[mmap[16][i]] = green; // right
    leds[mmap[i][16]] = green; // bottom
  }

  // set up the rest. IS THERE A BETTER WAY TO DO THIS?? ALGORITHM??
  leds[ mmap[9][1] ] = green;
  leds[ mmap[2][2] ] = green;
  leds[ mmap[3][2] ] = green;
  leds[ mmap[5][2] ] = green;
  leds[ mmap[6][2] ] = green;
  leds[ mmap[7][2] ] = green;
  leds[ mmap[9][2] ] = green;
  leds[ mmap[11][2] ] = green;
  leds[ mmap[12][2] ] = green;
  leds[ mmap[13][2] ] = green;
  leds[ mmap[14][2] ] = green;
  leds[ mmap[2][3] ] = green;
  leds[ mmap[3][3] ] = green;
  leds[ mmap[13][3] ] = green;
  leds[ mmap[14][3] ] = green;
  leds[ mmap[5][4] ] = green;
  leds[ mmap[7][4] ] = green;
  leds[ mmap[9][4] ] = green;
  leds[ mmap[11][4] ] = green;
  leds[ mmap[1][5] ] = green;
  leds[ mmap[2][5] ] = green;
  leds[ mmap[3][5] ] = green;
  leds[ mmap[5][5] ] = green;
  leds[ mmap[7][5] ] = green;
  leds[ mmap[9][5] ] = green;
  leds[ mmap[11][5] ] = green;
  leds[ mmap[12][5] ] = green;
  leds[ mmap[13][5] ] = green;
  leds[ mmap[14][5] ] = green;
  leds[ mmap[5][6] ] = green;
  leds[ mmap[7][6] ] = green;
  leds[ mmap[9][6] ] = green;
  leds[ mmap[2][7] ] = green;
  leds[ mmap[7][7] ] = green;
  leds[ mmap[9][7] ] = green;
  leds[ mmap[11][7] ] = green;
  leds[ mmap[12][7] ] = green;
  leds[ mmap[13][7] ] = green;
  leds[ mmap[14][7] ] = green;
  leds[ mmap[15][7] ] = green;
  leds[ mmap[2][8] ] = green;
  leds[ mmap[3][8] ] = green;
  leds[ mmap[4][8] ] = green;
  leds[ mmap[5][8] ] = green;
  leds[ mmap[7][8] ] = green;
  leds[ mmap[8][8] ] = green;
  leds[ mmap[9][8] ] = green;
  leds[ mmap[5][9] ] = green;
  leds[ mmap[11][9] ] = green;
  leds[ mmap[12][9] ] = green;
  leds[ mmap[13][9] ] = green;
  leds[ mmap[14][9] ] = green;
  leds[ mmap[2][10] ] = green;
  leds[ mmap[3][10] ] = green;
  leds[ mmap[5][10] ] = green;
  leds[ mmap[7][10] ] = green;
  leds[ mmap[8][10] ] = green;
  leds[ mmap[9][10] ] = green;
  leds[ mmap[11][10] ] = green;
  leds[ mmap[2][11] ] = green;
  leds[ mmap[3][11] ] = green;
  leds[ mmap[13][11] ] = green;
  leds[ mmap[15][11] ] = green;
  leds[ mmap[2][12] ] = green;
  leds[ mmap[3][12] ] = green;
  leds[ mmap[4][12] ] = green;
  leds[ mmap[6][12] ] = green;
  leds[ mmap[8][12] ] = green;
  leds[ mmap[9][12] ] = green;
  leds[ mmap[10][12] ] = green;
  leds[ mmap[11][12] ] = green;
  leds[ mmap[13][12] ] = green;
  leds[ mmap[15][12] ] = green;
  leds[ mmap[6][13] ] = green;
  leds[ mmap[10][13] ] = green;
  leds[ mmap[13][13] ] = green;
  leds[ mmap[2][14] ] = green;
  leds[ mmap[3][14] ] = green;
  leds[ mmap[4][14] ] = green;
  leds[ mmap[5][14] ] = green;
  leds[ mmap[6][14] ] = green;
  leds[ mmap[7][14] ] = green;
  leds[ mmap[8][14] ] = green;
  leds[ mmap[10][14] ] = green;
  leds[ mmap[12][14] ] = green;
  leds[ mmap[13][14] ] = green;
  leds[ mmap[14][14] ] = green;
  
  
}
