
import os
import sys

import re


rankBy = "Minimu"


deniedforduplicate = 0
deniedforcross = 0
notdenied = 0




inp = open(sys.argv[1], "r")
#out = open("sequenceROI", "w")

#outs = [open(o

#print(lens)
humdata = {}
wildata = {}
maxHum = 0
maxWil = 0
maxDog = 0
linenum = 0

while True:
    c = inp.readline()
    linenum += 1

    if not c:
        break
    if len(c) < 2:
        continue

    
    readnames = [int(s[5:]) for s in re.findall("read_[0-9]+", c)]
        
    if c[1] == 'D':
        data = humdata
        iswil = False
    elif c[1] == 'W':
        data = wildata
        iswil = True
    else:
        print("Oh no!")
    
    dogread = readnames[0]
    humread = readnames[1] 
    
    inp.readline() # eat these lines
    inp.readline()
    inp.readline()
    
    val = dict()
    skip = False
    for i in range(6):
        c = inp.readline()
        if len(c) == 0 or c == "\n" or c[0] == '\t':
            skip = True
            break
        c = c.split(' ')
        val[c[0][:-1]] = float(c[-1][:-1])
    
    if skip:
        continue
    
    if not dogread in data:
        data[dogread] = dict()
    
    data[dogread][humread] = val
    #print(val)
    #data.append((dogread, humread, val,))
    
    maxDog = max(dogread, maxDog)
    if iswil:
        maxWil = max(humread, maxHum)
    else:
        maxHum = max(humread, maxHum)
    
inp.close()



#def SummaryScore(data, maxhum):
    #summaryScore = 0
    #humStart = 0
    #numdogs = 0
    #numcomp = 0
    
    #for r in range(0, maxDog):
        #lastMax = -99999
        #lastMaxIdx = -1
        
        #if humStart >= maxhum:
            #break
        #if r not in data:
            #continue
        #numdogs += 1
        
        #for c in range(humStart, maxhum):
            #if c not in data[r]:
                #continue
            #if data[r][c] > lastMax:
                #lastMax = data[r][c]
                #lastMaxIdx = c
            #numcomp += 1
        
        #humStart = lastMaxIdx + 1
        #summaryScore += lastMax

    #print(str(summaryScore/numdogs) + "   " + str(numcomp))
   

def noCross(pair, pairs):
    global deniedforcross
    global deniedforduplicate
    global notdenied
    
    for p in pairs:
        if pair[0] == p[0] or pair[1] == p[1]:
            deniedforduplicate += 1
            return False
        
        if pair[0] > p[0]:
            if pair[1] < p[1]:
                deniedforcross+=1
                return False
        elif pair[0] < p[0]:
            if pair[1] > p[1]:
                deniedforcross+=1
                return False
    notdenied += 1
    return True


def SummaryScore2(data, maxhum):
    scores = []
    numdogs = 0
    numcomp = 0
    
    for r in range(0, maxDog):
        lastMax = -99999
        lastMaxIdx = -1
        
        if r not in data:
            continue
        numdogs += 1
        
        for c in range(0, maxhum):
            if c not in data[r]:
                continue
            if data[r][c][rankBy] > lastMax:
                lastMax = data[r][c][rankBy]
                lastMaxIdx = c
            numcomp += 1
        
        if lastMaxIdx >= 0:
            scores.append((r, lastMaxIdx, data[r][lastMaxIdx],))

    print(len(scores))
    scores = sorted(scores, key=lambda s : s[2][rankBy])
    
    totalScore = 0
    kept = []
    for i in scores:
        if noCross(i, kept):
            kept.append(i)
            totalScore += i[2][rankBy]

    print("sum score: " + str(totalScore))
    print("average score: " + str(totalScore/len(kept)))
    print("num dog reads: " + str(numdogs))
    print('total num read pairs: ' + str(numcomp))
    print("total num read pairs kept: " + str(len(kept)))
    

print("Beginning Analysis")

print("reg human")
SummaryScore2(humdata, maxHum)
print('\nwill human')
SummaryScore2(wildata, maxWil)
print("")

print("dup " + str(deniedforduplicate))
print("cross " + str(deniedforcross))
print("acc " + str(notdenied))


#for filename in os.listdir("3_WBSCR17_dog/reads/"):

#inputFormat({re.search("read_[0-9]+", filename).group(): "3_WBSCR17_dog/reads/"+filename for filename in os.listdir("3_WBSCR17_dog/reads/")} , "zukerScores.txt", "5_era_input_dog/")   
#inputFormat({re.search("read_[0-9]+", filename).group(): "3_WBSCR17_human/reads/"+filename for filename in os.listdir("3_WBSCR17_human/reads/")} , "zukerScores_Human.txt", "5_era_input_human/")   
