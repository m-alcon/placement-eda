#!/bin/bash

name="known_mesh_400_20x20"
./bin/visualization < ./data/input/${name}.in > ./data/output/graphviz/${name}.out
wait $!
./scripts/visualize.sh data/output/graphviz/${name}.out data/output/img/${name}.png