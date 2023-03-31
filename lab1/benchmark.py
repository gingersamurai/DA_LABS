from pprint import pprint
from matplotlib import pyplot as plt

import os
import time


if not os.path.exists("bench"):
    os.mkdir("bench")


ranges = (10, 50, 100, 500, 1_000, 5_000, 10_000)
sols = ('solution.cpp', 'base.cpp', 'dummy.cpp')

result = dict()
for sol in sols:
    result[sol] = []

for N in ranges:
    os.system(f"python3 gen.py {N} > bench/test_{N}")
    for sol in sols:
        start = time.time()
        os.system(f"g++ {sol} && ./a.out < bench/test_{N} > /dev/null")
        resultTime = time.time() - start
        result[sol].append(resultTime)
        print(f"{sol}\t\t{N}\t\t{float(resultTime)}")

pprint(result)

fig = plt.figure()
ax1 = fig.add_subplot(1, 1, 1)
for sol in sols:
    ax1.plot(ranges, result[sol], label=sol)
ax1.legend()
plt.show()