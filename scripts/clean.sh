#!/bin/bash

cd src
make clean
cd ..

if [ "$1" == "all" ]; then
    rm data/input/*
    rm data/known/*
    rm data/output/text/*
    rm data/output/img/*
fi