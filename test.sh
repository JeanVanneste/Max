#!/bin/sh

src/generate_data.py

./Max data 4 result 2> error.log

cat result
