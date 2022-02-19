
filename = "humanRefChr7_WBSCR17.fasta"
folder = "WBSCR17_HumanSequences/"

inp = open(filename, "r")
out = open(folder+filename, "w");

while True:
    c = inp.readline()
    
    if not c:
        break
    
    out.write(c.lower());
