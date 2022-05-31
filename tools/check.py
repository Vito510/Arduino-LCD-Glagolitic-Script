"""Checks if an input string will fit inside the 8 custom character limit."""
import sys
import json

if len(sys.argv) != 2:
    print("Usage: python3 check.py <string>")
    sys.exit(1)

data = json.load(open("./data.json"))

space = 0

cgram = []

for char in sys.argv[1]:
    if char.upper() in data and char.upper() not in cgram:
        if len(data[char.upper()]) > 8:
            space += 2
            cgram.append(char.upper())
            cgram.append(char.upper())
        else:
            space += 1
            cgram.append(char.upper())
    else:
        pass

print('Total space required:', space)
print('CGRAM: ',cgram)

if space > 8:
    print('String will NOT fit in LCD CGRAM')
else:
    print('String will fit in LCD CGRAM')
        