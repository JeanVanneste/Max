#!/usr/bin/python3

import random

filename = 'data'

data = open(filename, 'w')
for number in range(1000):
    data.write(str(random.randint(1, 1000000)) + '\n')
print("Nombres générés dans " + filename + "\n")