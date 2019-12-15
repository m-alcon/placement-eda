#!/usr/bin/python3

import argparse
import numpy as np
import sys

def print_warning (message):
    print("WARNING: %s"%message)

def print_error (message):
    print("ERROR: %s"%message)
    sys.exit()

def all_positions(w, h):
    return [(i,j) for j in range(w) for i in range(h)]

def generate_spiral(w, h):
    n, graph, positions = w*h, [[] for x in range(w*h)], [[] for x in range(w*h)]
    for i in range(h):
        if i%2 == 0:
            order = range(w)
            operation = 1
        else:
            order = reversed(range(w))
            operation = -1
        for j in order:
            u = i*w + j
            positions[u] = [i,j]
            j_aux = j + operation
            if j_aux >= 0 and j_aux < w:
                graph[u].append(str(j_aux + i*w))
                graph[j_aux + i*w].append(str(u))
            elif i+1 < h:
                graph[u].append(str((i+1)*w + j))
                graph[(i+1)*w + j].append(str(u))
    return n, graph, positions

def generate_mesh(w, h):
    n, graph, positions = w*h, [[] for x in range(w*h)], [[] for x in range(w*h)]
    for i in range(h):
        for j in range(w):
            u = i*w + j
            positions[u] = [i,j]
            if j + 1 < w:
                graph[u].append(str(i*w + j+1))
                graph[i*w + j+1].append(str(u))
            if i + 1 < h:     
                graph[u].append(str((i+1)*w + j))
                graph[(i+1)*w + j].append(str(u))
    return n, graph, positions

def generate_random(w, h, n):
    if not n:
        n = w*h
    graph, matrix= [], np.zeros((n,n))
    p = 3/n
    for i in range(n):
        for j in range(n):
            if i == j: continue
            choice = np.random.choice([0,1], 1, p=[1-p, p])
            matrix[i][j] = choice
            matrix[j][i] = choice
    for i in range(n):
        graph.append([str(j) for j in range(n) if matrix[i][j]])
    # positions = all_positions(w,h)
    # np.random.shuffle(positions)
    return n, graph #, positions[:n]

def generate_geometric(w, h, n):
    return n, []


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("width", type=int, help="Width of the surface")
    parser.add_argument("height", type=int, help="Height of the surface")
    parser.add_argument("-n", "--ncells", type=int, help="Number of cells")
    parser.add_argument("-t", "--type", choices=["spiral","mesh","random","geometric"], help="Type of the graph")
    #parser.add_argument("-f","--file", help="")
    args = parser.parse_args()
    n, w, h, t = args.ncells, args.width, args.height, args.type
    graph, positions = [], []
    if t == "spiral":
        if n: print_warning("Parameter NCELLS is not going to be used.")
        n, graph, positions = generate_spiral(w, h)
    elif t == "mesh":
        if n: print_warning("Parameter NCELLS is not going to be used.")
        n, graph, positions = generate_mesh(w, h)
    elif t == "random":
        if n and n > w*h:
            print_error("Not enough space for all the nodes (width*heigt < NCELLS).")
        else:
            n, graph = generate_random(w, h, n)
    elif t == "geometric":
        print_error("TODO: geometric")
    else:
        print_error("Non-defined graph type.")

    
    with open("data/input/problem_%s_%d_%dx%d.in"%(t, n, w, h), "w") as file:
        file.write("%d\n"%n)
        file.write("%d %d\n"%(w, h))
        for r in graph:
            file.write("%d %s\n"%(len(r), " ".join(r)))

    if positions:
        with open("data/input/known_%s_%d_%dx%d.in"%(t, n, w, h), "w") as file:
            file.write("%d\n"%n)
            file.write("%d %d\n"%(w, h))
            for [x,y],r in zip(positions, graph):
                file.write("%d %d %d %s\n"%(x, y, len(r), " ".join(r)))