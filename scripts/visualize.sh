#!/bin/bash

neato -Tpng $1 -o $2
xdg-open $2
