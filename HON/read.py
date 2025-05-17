from typing import Counter
import matplotlib.pyplot as plt
from matplotlib.scale import FuncScale
from matplotlib.ticker import FuncFormatter, ScalarFormatter
import numpy as np
from scipy.stats import beta


pkt = []
with open("samples/v2/b40a2_v2.txt", "r") as file:
    for l in file:
        pkt.append(l.strip())

count = Counter(pkt)
x = list(count.keys())
y = list(count.values())

plt.bar(x, y)
plt.show()
