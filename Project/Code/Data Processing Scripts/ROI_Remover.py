

def isolate(inputPath, outputdir, rois, names, LINE_LEN=80):
    inp = open(inputPath, "r")
    outputPathStart = inputPath.split(".")[0]
    outputPathEnd = inputPath.split(".")[-1]
    
    out = open(outputdir + "_without_" + "-".join(names) + "_" + inputPath.split("/")[-1], "w")

    i = 0
    leng = 0
    #print(lens)
    while True:
        c = inp.read(1)
        
        if not c:
            break
        
        if c == "\n":
            continue
        
        withinROI = False
        for o in range(len(rois)):
            roi = rois[o]
            
            if roi[0] <= i and i <= roi[1]:
                withinROI = True
                break
        
        if not withinROI:
            if leng % LINE_LEN == 0:
                out.write("\n")
            
            out.write(c)
            leng += 1
        
        i += 1
        
        if i % 1000000 == 0:
            print(i/1000000)
            
            
            
    inp.close()
    for out in outs:
        out.close()


rois = [(74027772,74122525)]
names = ["ELN", "LIMK1"]
isolate("2_sequence_human/humanRefChr7.fasta", "4_sequence_williams/", rois, names)
