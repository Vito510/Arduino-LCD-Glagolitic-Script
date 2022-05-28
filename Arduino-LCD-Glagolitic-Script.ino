#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

byte mem[][8] = {
        {B00000,B01110,B00100,B00100,B11111,B10101,B10101,B10101},
        {B00000,B10101,B10101,B10111,B11100,B10000,B10000,B11111},
        {B00000,B01101,B10101,B01101,B00101,B00110,B00010,B00010},
        {B00000,B01111,B01010,B01010,B01010,B01010,B01010,B01110},
        {B00000,B11000,B01000,B01000,B01000,B01110,B01010,B01110},
        {B00000,B01100,B10010,B00010,B00110,B00010,B10010,B01100},
        {B00000,B00100,B01110,B10101,B10101,B01110,B00100,B00100},
        {B00000,B00000,B11111,B10001,B01010,B00100,B01011,B10011},
        {B00000,B00000,B11111,B00001,B00010,B00100,B01011,B10011},
        {B00000,B01110,B01010,B01010,B01110,B01010,B01010,B01110},
        {B00000,B01010,B01010,B01010,B01111,B01010,B01010,B01010},
        {B00000,B01110,B01010,B01010,B11100,B01000,B01000,B01000},
        {B00000,B01110,B00100,B01000,B01110,B00010,B00010,B00010},
        {B00000,B00011,B00010,B01111,B01010,B01010,B01010,B01010},
        {B00000,B11000,B01000,B11110,B01010,B01010,B01010,B01010},
        {B00000,B01110,B10101,B10101,B10101,B01110,B10101,B00100},
        {B00000,B00111,B00101,B00101,B01110,B00100,B00100,B00100},
        {B00000,B01110,B01010,B01010,B00110,B01010,B01010,B01110},
        {B00000,B11111,B10101,B10101,B10111,B10000,B10000,B10000},
        {B00000,B01110,B01000,B01000,B01000,B01100,B01010,B01110},
        {B00000,B01110,B10001,B10001,B10101,B01010,B01010,B01110},
        {B00000,B01111,B01010,B01010,B01010,B01010,B01010,B01110},
        {B00000,B11110,B01010,B01010,B01010,B01010,B01010,B01110},
        {B00000,B11111,B10101,B10101,B01111,B10101,B10101,B11111},
        {B00000,B01110,B01010,B01010,B01010,B01010,B01010,B01111},
        {B00000,B01110,B01010,B01010,B01010,B01010,B01010,B11110},
        {B00000,B11100,B10100,B10100,B11100,B10100,B11011,B10011},
};

int map_[][4] = {{65,0,0},{66,0,1},{67,0,2},{68,1,3,4},{69,0,5},{70,0,6},{71,0,7},{72,0,8},{73,0,9},{74,1,10,11},{75,0,12},{76,1,13,14},{77,0,15},{78,0,16},{79,0,17},{80,0,18},{82,0,19},{83,0,20},{84,1,21,22},{85,0,23},{86,1,24,25},{90,0,26}};

void gprint(char x[]) {

  int x_int;
  int index;

  int count = 0;
  int char_count = 0;

  int cgram[8];

  int s = 0;

  for (int i = 0; i < strlen(x); i++) {
    x_int = toupper(x[i]);
    index = -1;

    //find index of char in map_ (hardcoded length)
    for (int i = 0; i < 22; i++) {
      if (x_int == map_[i][0]) {
          index = i;
      }
    }

    //does the glagolitic char require two chars?
    s = (map_[index][1] == 1) ? 2 : 1;

    for (int i = 0; i < s; i++) {
      //check if char is already in chars
      bool found = false;
      for (int j = 0; j < 8; j++) {
        if (map_[index][i+2] == cgram[j]) {
          found = true;
        }
      }

      //if not, add it
      if (!found) {
        cgram[char_count++] = map_[index][i+2];
      }

    }

  }


  //store chars in lcd memory (max 8 chars)
  for (int i = 0; i < char_count; i++) {
      int j = cgram[i];
      lcd.createChar(i, mem[j]);
  }


  lcd.home();

  //print chars
  for (int i = 0; i < strlen(x); i++) {
    //find char index in CGRAM
    int index = -1;
    bool double_char = false;

    //find char index in cgram
    for (int j = 0; j < 8; j++) {
      if (cgram[i] == x[i]) {
        index = j;

        //check if char requires two chars
        if (cgram[i+1] == x[i]) {
          double_char = true;
          }

      }
    }

      lcd.write(cgram[index]);
      if (double_char) {
        lcd.write(cgram[index+1]);
      }
      
  }  
  
}


void setup() {

  lcd.init();
  lcd.backlight();

  gprint("Vito");  


}

void loop() {}
