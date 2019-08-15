#!/usr/bin/python3

import random

filename = 'data'

data = open(filename, 'w')
max = 0
for i in range(100):
    number = random.randint(1, 999999999)
    data.write(str(number) + "\n")
    if number > max:
        max = number
print("Nombres générés dans " + filename)
print("Nombre max = " + str(max) + "\n")
