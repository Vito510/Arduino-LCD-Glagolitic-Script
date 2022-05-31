#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//#include <LiquidCrystal.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C

byte mem[][8] = {
    {B00000, B01110, B00100, B00100, B11111, B10101, B10101, B10101},
    {B00000, B10101, B10101, B10111, B11100, B10000, B10000, B11111},
    {B00000, B01101, B10101, B01101, B00101, B00110, B00010, B00010},
    {B00000, B01111, B01010, B01010, B01010, B01010, B01010, B01110},
    {B00000, B11000, B01000, B01000, B01000, B01110, B01010, B01110},
    {B00000, B01100, B10010, B00010, B00110, B00010, B10010, B01100},
    {B00000, B00100, B01110, B10101, B10101, B01110, B00100, B00100},
    {B00000, B00000, B11111, B10001, B01010, B00100, B01011, B10011},
    {B00000, B00000, B11111, B00001, B00010, B00100, B01011, B10011},
    {B00000, B01110, B01010, B01010, B01110, B01010, B01010, B01110},
    {B00000, B01010, B01010, B01010, B01111, B01010, B01010, B01010},
    {B00000, B01110, B01010, B01010, B11100, B01000, B01000, B01000},
    {B00000, B01110, B00100, B01000, B01110, B00010, B00010, B00010},
    {B00000, B00011, B00010, B01111, B01010, B01010, B01010, B01010},
    {B00000, B11000, B01000, B11110, B01010, B01010, B01010, B01010},
    {B00000, B01110, B10101, B10101, B10101, B01110, B10101, B00100},
    {B00000, B00111, B00101, B00101, B01110, B00100, B00100, B00100},
    {B00000, B01110, B01010, B01010, B00110, B01010, B01010, B01110},
    {B00000, B11111, B10101, B10101, B10111, B10000, B10000, B10000},
    {B00000, B01110, B01000, B01000, B01000, B01100, B01010, B01110},
    {B00000, B01110, B10001, B10001, B10101, B01010, B01010, B01110},
    {B00000, B01111, B01010, B01010, B01010, B01010, B01010, B01110},
    {B00000, B11110, B01010, B01010, B01010, B01010, B01010, B01110},
    {B00000, B11111, B10101, B10101, B01111, B10101, B10101, B11111},
    {B00000, B01110, B01010, B01010, B01010, B01010, B01010, B01111},
    {B00000, B01110, B01010, B01010, B01010, B01010, B01010, B11110},
    {B00000, B11100, B10100, B10100, B11100, B10100, B11011, B10011},
};

int map_[][4] = {{65, 0, 0}, {66, 0, 1}, {67, 0, 2}, {68, 1, 3, 4}, {69, 0, 5}, {70, 0, 6}, {71, 0, 7}, {72, 0, 8}, {73, 0, 9}, {74, 1, 10, 11}, {75, 0, 12}, {76, 1, 13, 14}, {77, 0, 15}, {78, 0, 16}, {79, 0, 17}, {80, 0, 18}, {82, 0, 19}, {83, 0, 20}, {84, 1, 21, 22}, {85, 0, 23}, {86, 1, 24, 25}, {90, 0, 26}};

int getmap(int c)
//Find the index of the char in the lookup table
{
  for (int i = 0; i < 22; i++)
  {
    if (c == map_[i][0])
    {
      return i;
    }
  }
  return -1;
}

bool contains(int x, int arr[])
//Does the array contain the value x?
{
  for (int i = 0; i < 8; i++)
  {
    if (arr[i] == x)
    {
      return true;
    }
  }
  return false;
}

void gprint(char x[])
{

  int cgram[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
  int cgmap[8] = {-1, -1, -1, -1, -1, -1, -1, -1};

  int char_count = 0;

  int location;
  bool dual;

  //Add the characters to the cgram
  for (int i = 0; i < strlen(x); i++)
  {

    //Find the index of the char in the lookup table
    location = getmap(x[i]);

    if (location != -1)
    {

      for (int k = 0; k < map_[location][1] + 1; k++)
      {
        //Check if the character is already in the cgram
        if (!contains(map_[location][2 + k], cgram))
        {
          cgram[char_count] = map_[location][k + 2];
          cgmap[char_count] = map_[location][0];
          char_count++;
        }
      }
    }
  }

  // get size of cgram
  int cgram_size = 0;

  for (int i = 0; i < 8; i++)
  {
    if (cgram[i] != -1)
    {
      cgram_size++;
    }
  }

  // Serial.begin(9600);
  // Serial.print("CGRAM used: ");
  // Serial.print(cgram_size);
  // Serial.print("/8");
  // Serial.println("");

  // Write to lcd cgram
  for (int i = 0; i < cgram_size; i++)
  {
    lcd.createChar(i, mem[cgram[i]]);
  }

  lcd.home();

  // Print to lcd

  //for every character in input string
  for (int i = 0; i < strlen(x); i++) {
    location = -1;
    //find location of char in cgram
    for (int j = 0; j < cgram_size; j++)
    {
      if (cgmap[j] == x[i])
      {
        location = j;

        dual = (cgmap[j + 1] == x[i]) ? true : false;

        break;
      }
    }

    //if not found, print without converting
    if (location == -1)
    {
      lcd.print(x[i]);
    }
    else 
    {
      lcd.write(location);

      //if the char requires a second character print it
      if (dual) {
        lcd.write(location + 1);
      }

    }
  }
}

void setup()
{

  lcd.init();
  lcd.backlight();

  //print input in glagolitic script (ONLY UPPERCASE GETS CONVERTED)
  gprint("VITO");
}

void loop() {}
