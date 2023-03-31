import random
import sys
alp = "0123456789abcdef"

n = int(sys.argv[1])
for _ in range(n):
    key = "".join([random.choice(alp) for i in range(32)])
    value = random.randint(0, 100)
    print(key, value, sep="\t")
