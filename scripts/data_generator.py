#!/usr/bin/python3

import argparse
import numpy as np
import sys

def print_warning (message):
    print("WARNING: %s"%message)

def print_error (message):
    print("ERROR: %s"%message)

def generate_spiral(w, h):
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
            j_aux = j + operation
            if j_aux >= 0 and j_aux < w:
                graph[u].append(str(j_aux + i*w))
                graph[j_aux + i*w].append(str(u))
            elif i+1 < h:
                graph[u].append(str((i+1)*w + j))
                graph[(i+1)*w + j].append(str(u))
    return n, graph

def generate_mesh(w, h):
    n, graph = w*h, [[] for x in range(w*h)]
    for i in range(h):
        for j in range(w):
            u = i*w + j
            if j + 1 < w:
                graph[u].append(str(i*w + j+1))
                graph[i*w + j+1].append(str(u))
            if i + 1 < h:     
                graph[u].append(str((i+1)*w + j))
                graph[(i+1)*w + j].append(str(u))
    return n, graph

def generate_random(w, h, n):
    if not n:
        n = w*h
    matrix = np.zeros((n,n))
    p = 0.5
    for i in range(n):
        for j in range(n):
            matrix[i][j] = np.random.choice([0,1], 1, p=[1-p, p])
    positions = np.random.choice(range(w*h),n)
    var = 0
    for i in range(h):
        for j in range(w):
            if i*w + j in positions:
                graph[1]
    return graph


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("width", type=int, help="Width of the surface")
    parser.add_argument("height", type=int, help="Height of the surface")
    parser.add_argument("-n", "--ncells", type=int, help="Number of cells")
    parser.add_argument("-t", "--type", choices=["spiral","mesh","random","geometric"], help="Type of the graph")
    #parser.add_argument("-f","--file", help="")
    args = parser.parse_args()
    n, w, h, t = int(args.ncells), int(args.width), int(args.height), args.type
    graph = []
    if t == "spiral":
        if n: print_warning("Parameter NCELLS is not going to be used.")
        n, graph = generate_spiral(w, h)
    elif t == "mesh":
        if n: print_warning("Parameter NCELLS is not going to be used.")
        n, graph = generate_mesh(w, h)
    elif t == "random":
        if n <= w*h:
            graph = generate_random(w, h, n)
        else:
            print_error("Not enough space for all the nodes (width*heigt < NCELLS).")
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
