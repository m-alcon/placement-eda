# Placement solver for Electronic Design Automation

## How to use

#### Generate data
The following script generates the data and saves it in `data/input/` folder.
```
./scripts/generate_data -t TYPE [-n NODES] W H
```

Parameters:
+ **TYPE** can be *spiral*, *mesh* or *random*.
+ **NODES** is the number of nodes of the data you want to generate.
+ **W** and **H** are the width and the height of the 2D surface.


Generated files has the following name: `problem_TYPE_NODES_WxH.in`.
If the problem has a known solution, it is also saved as `known_TYPE_NODES_WxH.in`.

### Build the code
```
./scripts/build.sh
```

### Execute the algorithm and visualize the solution
The following script creates two file:
+ One with the solution as a *graphviz* input inside `data/output/graphviz/` folder named `problem_TYPE_NODES_WxH.out`.
+ The other as an image inside `data/output/img/` named `problem_TYPE_NODES_WxH.png`.
```
./bin/execute.sh NAME EQUILIBRIUM IT_MAX
```

Parameters:
+ **NAME** is the name of the problem's file (`problem_TYPE_NODES_WxH`).
+ **EQUILIBRIUM** is the consecutive number of iterations the algorithm can do without improving the solution inside the temperature loop.
+ **IT_MAX** is the maximum number of iterations the algorithm can do inside the temperature loop.


### Compute the cost and visualize the known solution
The following script creates two file:
+ One with the solution as a *graphviz* input inside `data/output/graphviz/` folder named `known_TYPE_NODES_WxH.out`.
+ The other as an image inside `data/output/img/` named `known_TYPE_NODES_WxH.png`.
```
./bin/execute_known.sh NAME
```
Parameters:
+ **NAME** is the name of the known problem's file (`known_TYPE_NODES_WxH`).
