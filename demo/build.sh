#!/bin/sh
gcc $1 `pkg-config --libs --cflags  gtk+-3.0` -o demo
./demo
