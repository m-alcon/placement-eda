#!/bin/bash

name=$1
./bin/visualization < ./data/input/${name}.in > ./data/output/graphviz/${name}.out
wait $!
./scripts/visualize.sh data/output/graphviz/${name}.out data/output/img/${name}.png