

# ############################
#
#  SRA to FASTQ
#
# ############################

for sra in 0_sra_dog/*; do
   ../sratoolkit.2.9.6-1-ubuntu64/bin/fastq-dump $sra
done
mv *.fastq 1_fastq_dog/

for sra in 0_sra_wolf/*; do
   ../sratoolkit.2.9.6-1-ubuntu64/bin/fastq-dump $sra
done
mv *.fastq 1_fastq_wolf/


# ############################
#
#  FASTQ to Sequence
#
# ############################

for fastq in 1_fastq_dog/*; do
    awk '{if(NR%4==2) print $0}' $fastq > $fastq.seq
done

mv 1_fastq_dog/*.seq 2_sequence_dog/

for fastq in 1_fastq_wolf/*; do
    echo $fastq
    awk '{if(NR%4==2) print $0}' $fastq > $fastq.seq
done

mv 1_fastq_wolf/*.seq 2_sequence_wolf/



