import sys

inpPath = sys.argv[1]
inp = open(inpPath, 'r')
readSize = int(sys.argv[2])
overlap = int(sys.argv[3])

if overlap > readSize // 2:
    raise Exception("overlap must be at most half the read size")

try:
    decIdx = inpPath.index('.')
except:
    decIdx = len(inpPath)
    

inpPath0 = inpPath[0:decIdx]
impPathF = inpPath[decIdx:]


out = open(inpPath0+"_read_0"+impPathF, "w+")
out2 = None

readCount = 1
i = 0
curLen = 0
while True:
    c = inp.read(1)
    
    if not c:
        break
    
    if c == '\n':
        continue
    
    if i != 0 and curLen == readSize-overlap:
        out2 = open(inpPath0+"_read_"+str(readCount)+impPathF, "w+")
        readCount += 1
        
    
    if i != 0 and curLen >= readSize:
        out.close()
        out = out2 #open(inpPath0+"_read_"+str(readCount)+impPathF, "w+")
        out2 = None
        curLen = overlap
    
    if c == 'T':
        c = 'U'
    if c == 't':
        c = 'u'
    
    out.write(c);
    curLen += 1
    
    if(out2 != None):
        out2.write(c);


    i += 1
    
