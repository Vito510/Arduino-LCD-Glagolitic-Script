"""Appends input.txt to json"""
import json

x = open("input.txt", "r").readlines()

for item in range(len(x)):
    x[item] = x[item].strip()
    x[item] = x[item].replace("\n", "")
    x[item] = x[item].replace(",", "")
    x[item] = x[item].replace("B", "")



print(x)

data = json.load(open('data.json'))

key = input('>')

data[key.upper()] = x
json.dump(data, open('data.json', 'w'), indent=4)