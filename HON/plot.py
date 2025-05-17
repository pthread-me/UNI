from typing import Counter
import matplotlib.pyplot as plt
from matplotlib.scale import FuncScale
from matplotlib.ticker import FuncFormatter, ScalarFormatter
import numpy as np
from scipy.stats import beta

sample = "b10a10"

file = f"samples/v3/{sample}.out"
file_baseline = f"samples/output/baselines/{sample}.baseline"


def get_sum(filename):
    raw: list [int]  = []
    comp: list [int]  = []
    pen: list [int]  = []
    sum: list[float] = []

    with open(filename) as file:
        for line in file:
            l = line.strip().split(",")
            raw.append(int(l[0]))
            comp.append(int(l[1]))
            pen.append(int(l[2]))
        
            sum.append(int(l[1]) + int(l[2]))
    return sum

def aggregate(sum: list[float]):

    aggregate: list[float] = []
    for i in range(0, len(sum)//10):
        avg = 10
        for j in range(i, i+10):
            avg += sum[j]
        aggregate.append(avg/10)
    return aggregate

def cdf(sum: list[float]):
    c: list[float] = []
    cdf: list[float]= []

    for i in range(0, len(sum)):
        if i == 0:
            cdf.append(sum[i])
            c.append(sum[i])
        else:
            x = (sum[i]+c[i-1])
            c.append(x)
            cdf.append(x/(i+1))
    return cdf

def total_avg(name: str, avg:list[float]):
    sum = 0
    for i in avg:
        sum += i
    print(f"Total average of {name}: {sum/len(avg)}")


if __name__ == "__main__":

    sum = get_sum(file)
    base_sum = get_sum(file_baseline)

#    avg= aggregate(sum)
    com = cdf(sum)
    base_com = cdf(base_sum)
 #   base_avg = aggregate(base_sum)

    time = list(range(0, len(sum)))

    plt.xlabel("Packets Sent")
    plt.ylabel("Average Header Size (Bytes)")

    ax = plt.gca()
    formatter = ScalarFormatter(useMathText=True)
    formatter.set_scientific(True)
    formatter.set_powerlimits((2,2))
        
    ax.xaxis.set_major_formatter(formatter)

    plt.plot(time, com, color='b', label="Dynamic updating")
#    plt.plot(time, uavg, color='b', label="dynamic rules, update freq=500")
    plt.plot(time, base_com, color='r', label="Control")

    plt.legend(loc="upper left")
#    plt.show()
#    plt.savefig(f"graphs/{sample}.png", dpi=500)
    
    total_avg("First", sum)
#    total_avg("Updated", uavg)
    total_avg("Baseline", base_sum)


