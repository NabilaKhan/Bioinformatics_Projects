

def isolate(inputPath, outputdir, rois, names, LINE_LEN=80):
    inp = open(inputPath, "r")
    #out = open("sequenceROI", "w")
    outputPathStart = inputPath.split(".")[0]
    outputPathEnd = inputPath.split(".")[-1]
    
    outs = [open(outputdir + name + "_" + inputPath.split("/")[-1], "w") for name in names]

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
                
                if lens[o] % LINE_LEN == 0:
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


rois = [(74657665,74760692), (74453906,74603070)]
names = ["GTF2I", "GTF2IRD1"]#["GTF2I", "GTF2IRD1", "WBSCR17"]
isolate("2_sequence_human/humanRefChr7.fasta", "5_OtherTwo_human/", rois, names)
