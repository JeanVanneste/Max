#!/usr/bin/python3

import random

filename = 'data'

data = open(filename, 'w')
max = 0
for number in range(10):
    number = random.randint(1, 100)
    data.write(str(number) + '\n')
    if number > max:
        max = number
print("Nombres générés dans " + filename + "\n")
print("Nombre max = " + str(max))
