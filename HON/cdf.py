from typing import Counter
import matplotlib.pyplot as plt
from matplotlib.scale import FuncScale
from matplotlib.ticker import FuncFormatter, ScalarFormatter
import numpy as np
from scipy.stats import beta

sample = "b40a2"

file = f"samples/output/{sample}.out"
file_baseline = f"samples/output/baselines/{sample}.baseline"


def get_comp(filename):
    comp: list [float]  = []

    with open(filename) as file:
        for line in file:
            l = line.strip().split(",")
            a = int(l[1])
            b = int(l[0])
            p = round(a/b, 2)
            comp.append(p)
    return comp


def cdf(c:list[int]):
    comp = Counter(c)
    n = len(c)
    prob: list[float] = []

    for i in np.arange(0, 1.05, .01):
        if i == 0:
            prob.append(comp[i]/n)
        else:
            prob.append((prob[len(prob)-1]) + (comp[i]/n)) 
#        print(f"cum={prob[len(prob)-1]} \t cur={comp[i]}")

    return prob
if __name__ == "__main__":
    comp = get_comp(file)
    p = cdf(comp)
    plt.xlabel("Compression factor")
    plt.ylabel("Probability")

#    ax = plt.gca()
#    formatter = ScalarFormatter(useMathText=True)
#    formatter.set_scientific(True)
#    formatter.set_powerlimits((2,2))
        
#    ax.xaxis.set_major_formatter(formatter)

    n = list(np.arange(0,1.05, 0.01))
    plt.plot(n, p, color='b')
#    plt.plot(time, uavg, color='g')
#    plt.plot(time, base_avg, color='r')

    plt.show()
#    plt.savefig(f"graphs/{sample}.png", dpi=500)
    
#    total_avg("First", avg)
#    total_avg("Updated", uavg)
#    total_avg("Baseline", base_avg)

