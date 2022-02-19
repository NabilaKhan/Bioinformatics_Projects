
import os

def roiIsolate(filename, outputdir, rois, names, lineLen=80):
    inp = open(filename, "r")
    #out = open("sequenceROI", "w")
    
    outs = [open(outputdir + name + "_" + filename.split("/")[-1], "w") for name in names]

    i = 0
    lens = [0]*len(rois)
    #print(lens)
    while True:
        c = inp.read(1)
        
        if not c:
            break
        
        if c == "\n":
            continue
        
        oneNotOver = False
        for o in range(len(rois)):
            roi = rois[o]
            out = outs[o] 
            oneNotOver = oneNotOver or i <= roi[1]
            
            if roi[0] <= i and i <= roi[1]:
                out.write(c)
                lens[o] += 1
                
                if lens[o] % lineLen == 0:
                    #print(lens[o])
                    #out.write("     " + str(lens[o]) + "\n")
                    out.write("\n")
        
        if not oneNotOver:
            break;
        
        i += 1
        
        if i % 1000000 == 0:
            print(i/1000000)
            
            
            
    inp.close()
    for out in outs:
        out.close()



rois = [(5726652,5840740), (5887757,5997627)]
names = ["GTF2I", "GTF2IRD1"]#["GTF2I", "GTF2IRD1", "WBSCR17"]

for filename in os.listdir("2_sequence_wolf/"):
    roiIsolate("2_sequence_wolf/"+filename, "5_OtherTwo_wolf/", rois, names)

for filename in os.listdir("2_sequence_dog/"):
    roiIsolate("2_sequence_dog/"+filename, "5_OtherTwo_dog/", rois, names)
