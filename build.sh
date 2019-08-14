#!/bin/sh

src/generate_data.py
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug 
