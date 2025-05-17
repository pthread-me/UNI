from typing import Counter
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import beta

pkts: list[str] = []

file_name = "samples/b10a10.txt"

with open(file_name) as file:
    for line in file:
        l = line.strip().split()[0:4]
        #pkts.append("".join(l))
        pkts.append(line.strip())
freq = Counter(pkts)

labels:list[str] = []
#for p in pkts:
#    i = p.split(' ')[4]
#    labels.append(i)
 

keys = list(freq.keys())
x = list(range(0, len(keys)))
#print(x)
y = list(freq.values())

plt.bar(x , y)
plt.xticks(labels)
plt.show()
 
#for k, f in sorted(freq.items(), key=lambda x: x[1], reverse=True):
#    print(k, f)
