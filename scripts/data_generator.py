import argparse

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("n", type=int, help="Number of cells")
    parser.add_argument("width", type=int, help="Width of the surface")
    parser.add_argument("height", type=int, help="Height of the surface")
    #parser.add_argument("-f","--file", help="")
    args = parser.parse_args()
    n, w, h = args.n, args.width, args.height
    with open("data/problem_%d_%dx%d.dat"%(n, w, h), "w") as file:
        file.write("%d\n"%n)
        file.write("%d %d\n"%(w, h))
