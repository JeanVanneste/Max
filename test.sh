#!/bin/sh

src/generate_data.py

./Max data 4 result 2> error.log

if [ $? -ne 0 ]; then
    echo "\nError: check error.log"
else
    echo ""
    cat result
fi