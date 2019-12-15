#!/bin/bash

cd src
make clean
cd ..

if [ "$1" == "all" ]; then
    rm data/input/*
    rm data/known/*
    rm data/output/graphviz/*
    rm data/output/img/*
elif [ "$1" == "output" ]; then
    rm data/output/graphviz/* data/output/img/* data/output/costs.txt
fi