# Arduino-LCD-Glagolitic-Script
Display Glagolitic script on an Arduino LCD (HD44780)

A little school project of mine.

<hr>

<img src="https://user-images.githubusercontent.com/73427833/171829980-9ee50c14-8bf1-471d-aa6c-3fcf91f6cc77.jpg" width="500">

<i>Vito</i> in glagolitic script



# Custom character limit
Sadly the HD44780 and other similar Arduino lcds have a 8 (5x8) custom character limit this is due to the limited size of the CGRAM on the LCD and since some of the glagolithic chars dont fit in a 5x8 grid they require double the space.

**To check if a string will fit within the CGRAM use check.py in the tools folder**
