#!/bin/sh
gcc $1 `pkg-config --libs --cflags  gtk+-2.0` -o demo
