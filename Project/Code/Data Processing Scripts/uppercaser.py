
filename = "humanRefChr7_WBSCR17.fasta.seq"
folder = "3_WBSCR17_human/"

inp = open(filename, "r")
out = open(folder+filename, "w");

while True:
    c = inp.readline()
    
    if not c:
        break
    
    out.write(c.upper());
