#!/bin/bash

rm -f threads

gcc -pthread countdownlatch.c main.c -o threads

exec ./threads $1
