#!/usr/bin/python3

import argparse
import sys

def print_warning(message):
    print("WARR: %s"%message)

def generate_spiral(w,h):
    n, graph = w*h, [[] for x in range(w*h)]
    for i in range(h):
        if i%2 == 0:
            order = range(w)
            operation = 1
        else:
            order = reversed(range(w))
            operation = -1
        for j in order:
            u = i*w + j
            v = j + operation
            if v >= 0 and v < w:
                graph[u].append(str(v + i*w))
            elif i+1 < h:
                graph[u].append(str((i+1)*w + j))
    return n, graph

def generate_mesh(w,h):
    n, graph = 0, []
    return n, graph

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("width", type=int, help="Width of the surface")
    parser.add_argument("height", type=int, help="Height of the surface")
    parser.add_argument("-n", "--ncells", type=int, help="Number of cells")
    parser.add_argument("-t", "--type", choices=["spiral","mesh","random","geometric"], help="Type of the graph")
    #parser.add_argument("-f","--file", help="")
    args = parser.parse_args()
    n, w, h, t = args.ncells, args.width, args.height, args.type
    graph = []
    if t == "spiral":
        if n: print_warning("Parameter NCELLS is not going to be used.")
        n, graph = generate_spiral(w,h)
    elif t == "mesh":
        if n: print_warning("Parameter NCELLS is not going to be used.")
        n, graph = generate_mesh(w,h)
    elif t == "random":
        n = 0
        print("random")
    elif t == "TODO: geometric":
        n = 0
        print(":TODO: geometric")
    else:
        print("Non-defined graph type.")
        sys.exit()

    with open("data/problem_%s_%d_%dx%d.dat"%(t, n, w, h), "w") as file:
        file.write("%d\n"%n)
        file.write("%d %d\n"%(w, h))
        for r in graph:
            file.write(str(len(r))+" "+" ".join(r)+"\n")
