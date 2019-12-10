#!/bin/bash

./bin/placement < ./data/known/problem_spiral_25_5x5.in > ./data/output/adjacency/problem_spiral_25_5x5.out
wait $!
./scripts/visualize.sh data/output/adjacency/problem_spiral_25_5x5.out data/output/img/problem_spiral_25_5x5.png