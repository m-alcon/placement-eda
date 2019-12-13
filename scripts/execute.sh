#!/bin/bash

name="problem_random_25_5x5"
./bin/placement < ./data/input/${name}.in > ./data/output/graphviz/${name}.out
wait $!
./scripts/visualize.sh data/output/graphviz/${name}.out data/output/img/${name}.png