import os
import sys

import re

def read(filepath, data):
    inp = open(filepath, "r")
    
    maxHum = 0
    maxDog = 0

    while True:
        c = inp.readline()

        if not c:
            break
        if len(c) < 2:
            continue

        readnames = [int(s[5:]) for s in re.findall("read_[0-9]+", c)]
        
        dogread = readnames[1]
        humread = readnames[0] 
        
        val = dict()
        skip = False
        for i in range(9):
            c = inp.readline()
            if len(c) == 0 or c == "\n" or c[0] == '\t':
                skip = True
                break
            c = c.split('\t')
            val[c[0][:-1]] = int(c[1][:-1])
        
        if skip:
            continue
        
        data.append((dogread, humread, val,))
        
        maxDog = max(dogread, maxDog)
        maxHum = max(humread, maxHum)
        
    inp.close()


data = []
read(sys.argv[1], data)
read(sys.argv[2], data)

#data = [d for d in data if "Score" in d[2]]
data = sorted(data, key=lambda s : -s[2]["Score"])

for i in range(1):
    print("Best Aligned Reads:" + str(data[i]))
    
s = 0
l = len(data)
for d in data:
    s += d[2]["Score"] / l
print("Average Score across all pairs: " + str(s))
