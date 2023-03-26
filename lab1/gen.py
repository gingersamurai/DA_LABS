import random

alp = "0123456789abcdef"

n = 100
for _ in range(n):
    key = "".join([random.choice(alp) for i in range(32)])
    value = random.randint(0, 100)
    print(key, value, sep="\t")
