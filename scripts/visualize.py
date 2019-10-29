from graphviz import Graph

dot = Graph(comment='Graph')

with open("./data/problem_spiral_15_3x5.dat") as file:
    n = int(file.readline())
    w, h = file.readline().split()
    adjacency = []
    for l in file.readlines():
        adjacency.append(l.split()[1:])

for i in range(n):
    dot.node(str(i))

for i in range(n):
    for v in adjacency[i]:
        dot.edge(str(i),v)
dot.render('test-output/round-table.gv', view=True)  

#neato -Tpng data/graphviz.test -o output.v1.png
