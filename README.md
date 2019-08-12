# Max

## What is Max

Max is a software designed to extract the maximum number in a text file containing one number by line, write it in a separate file using multithreading to accelerate the process.

## How to use Max

In a shell, use

```sh
./Max input nb output
```

where input is the text file with the data, output a filename where to write result and nb the number of thread to use.

For example,

```sh
./Max data.txt 4 result.txt
```

will write the max number in data.txt to result.txt using 4 different thread

## Caution

Max will overwrite the output file.

## Compilation

Required :

- gcc
- cmake
- POSIX thread library
- python3

The script build.sh will generate a list of number in the *data* file and will generate a debug Makefile to allow you to use a debugger.

The script release.sh can be use to generate the Makefile for an optimized executable.

The script used to generate the data file is located inside the src folder and is called generate_data.py.
