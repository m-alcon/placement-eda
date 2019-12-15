#!/bin/bash

name=$1
./bin/placement $name $2 $3
wait $!
./scripts/visualize.sh data/output/graphviz/${name}.out data/output/img/${name}.png