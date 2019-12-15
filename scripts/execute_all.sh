#!/bin/bash

echo "" > data/output/costs.txt
for name in `cat data/input_files.txt`; do
    echo "$name"
    ./bin/placement $name 2>> data/output/costs.txt  
    wait $!
    ./scripts/visualize.sh data/output/graphviz/${name}.out data/output/img/${name}.png
done