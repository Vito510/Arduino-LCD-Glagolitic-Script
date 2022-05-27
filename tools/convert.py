"""Converts json to a byte array which can then be copy-pasted to the Arduino source code"""
import json

data = json.load(open('data.json'))

x = "byte mem[][8] = {\n"

for key in data:
    x += "\t{"
    c = 0
    for item in data[key]:

        if c == 7 and len(data[key]) > 8:
            x += "B" + item + "},\n\t{"
        else:
            x += "B" + item + ","

        c += 1
    x = x[:-1]
    x += "},\n"

x += "};"

print(x+"\n")


x = "int map_[][2] = {"
c = 0
for key in data:
    if len(data[key]) > 8:
        x += '{' + f'{ord(key)},{c},{c+1}'
        c += 1
    else:
        x += '{' + f'{ord(key)},{c},'
        x = x[:-1]
    x += '},'
    c += 1

x = x[:-1]
x += '};'

print(x)