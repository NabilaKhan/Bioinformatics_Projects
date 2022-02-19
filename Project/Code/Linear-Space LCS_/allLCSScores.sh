# #############################################################
#
#  EXPECTED FOLDER STRUCTURE:
#  
#  [parentFolder]/
#       allLCSScores.sh
#       src/
#           lcs/
#              LCS_Only_Score.cpp 
#       build/
#       output/
#       data/
#           3_WBSCR17_human/
#               [human sequences]
#           3_WBSCR17_dog/
#               [dog sequences]
#           3_WBSCR17_wolf/
#               [wolf sequences]
#
#  Run from the same folder allLCSScores.sh is in
#  
# #############################################################

SRC=src/lcs/LCS_Only_Score.cpp
EXE=build/lcs_scoreOnly.out
OUTPUT=output/lcsScores.txt

HUMAN_SEQS=data/3_WBSCR17_human/*
DOG_SEQS=data/3_WBSCR17_dog/*
WOLF_SEQS=data/3_WBSCR17_wolf/*

# compile main script
g++ $SRC -o $EXE

# clear output file
printf "" > $OUTPUT

HUMAN_COUNT=0

# for each human sequence, compare it to each dog and each wolf sequence
for humanSeq in $HUMAN_SEQS; do
    echo "Processing human "$HUMAN_COUNT
    
    DOG_COUNT=0
    for dogSeq in $DOG_SEQS; do
        printf "\tdog "$DOG_COUNT"\n"
        
        printf "\tDOG : "$humanSeq" "$dogSeq":\n" >> $OUTPUT
        $EXE $humanSeq $dogSeq >> $OUTPUT
        
        DOG_COUNT+=1
    done
    
    WOLF_COUNT=0
    for wolfSeq in $WOLF_SEQS; do
        printf "\twolf "$WOLF_COUNT"\n"
        
        printf "\tWOLF: "$humanSeq" "$wolfSeq":\n" >> $OUTPUT
        $EXE $humanSeq $wolfSeq >> $OUTPUT
        
        WOLF_COUNT+=1
    done
    
    echo "" >> $OUTPUT
    echo "" >> $OUTPUT
    
    HUMAN_COUNT+=1
done
