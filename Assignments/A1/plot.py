import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import make_interp_spline
from sys import argv

if __name__ == "__main__":
    file = argv[1]
    n, p = map(lambda x: int(float(x)), file[file.index('/') + 1:file.index('.') + 1].split('_')[:2])
    with open(file) as f:
        lines = f.readlines()
    num_threads = (len(lines) - 1) // 5
    x = []
    y = []
    for numt in range(0, num_threads):
        x.append(int(lines[3 + numt * 5].split()[-1]))
        y.append(float(lines[(numt + 1) * 5].split()[-1][:-2]) / 1e3)
    y = [e for _, e in sorted(zip(x, y))]
    x.sort()
    X = np.linspace(x[0], x[-1], 250)
    plt.plot(X, make_interp_spline(x, y, k=2)(X), label="Smooth plot")
    plt.scatter(x, y, color="red", label="Time taken")
    plt.xlabel("Number of Threads")
    plt.ylabel("Time taken (in seconds)")
    plt.title(f"$n = {n}, p = {p}$")
    plt.legend()
    plt.savefig(file[:-3] + "png")
