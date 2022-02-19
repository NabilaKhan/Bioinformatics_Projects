
import os
import re

def inputFormat(files, scoresPath, outputdir, lineLen=80):
    inp = open(scoresPath, "r")
    #out = open("sequenceROI", "w")
    
    #outs = [open(outputdir + name + "_" + filename.split("/")[-1], "w") for name in names]

    inp.readline()
        
    #print(lens)
    while True:
        c = inp.readline()
        
        if not c:
            break
        
        print(c)
        readname = re.search("read_[0-9]+", c).group()
        
        inp.readline() # toss these
        inp.readline()
        inp.readline()
        
        c = inp.readline() + inp.readline()
        c = "".join([char for char in c if char != " "])
        
        tempInp = open(files[readname], "r")
        
        out = open(outputdir+readname, "w+")
        out.write(">AY012114.1954_1022\n")
        out.write(tempInp.readline()+"\n")
        out.write(c+"\n")
        
        tempInp.close()
        out.close()
        
        inp.readline()
            
    inp.close()


#for filename in os.listdir("3_WBSCR17_dog/reads/"):

inputFormat({re.search("read_[0-9]+", filename).group(): "3_WBSCR17_dog/reads/"+filename for filename in os.listdir("3_WBSCR17_dog/reads/")} , "zukerScores.txt", "5_era_input_dog/")   
inputFormat({re.search("read_[0-9]+", filename).group(): "3_WBSCR17_human/reads/"+filename for filename in os.listdir("3_WBSCR17_human/reads/")} , "zukerScores_Human.txt", "5_era_input_human/")   
