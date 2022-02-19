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

EXE=./src/ERA_v1.0/ERA
OUTPUT=output/eraScores.txt
TEMP=output/eraScores_temp.txt

HUMAN_SEQS=data/5_era_input_human/*
DOG_SEQS=data/5_era_input_dog/*

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
        $EXE -i $humanSeq -j $dogSeq > $TEMP
        
        grep Score $TEMP >> $OUTPUT
        grep lengthS $TEMP >> $OUTPUT
        grep lengthT $TEMP >> $OUTPUT
        grep pairs $TEMP >> $OUTPUT
        grep num $TEMP >> $OUTPUT
        
        DOG_COUNT+=1
    done
    
    echo "" >> $OUTPUT
    echo "" >> $OUTPUT
    
    HUMAN_COUNT+=1
done
