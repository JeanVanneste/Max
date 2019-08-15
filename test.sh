#!/bin/sh

src/generate_data.py

./Max data 4 result 2> error.log

if [ $? -ne 0 ]; then
    echo "Error: check error.log"
else
    cat result
fi