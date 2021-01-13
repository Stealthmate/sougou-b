load 'gnuplot/common.gp'
set xlabel 'Trial Number'
set ylabel 'CDR'
set yrange [0:1.1]
plot inputfile using 1:3 with line lw 2 title "S1", \
     inputfile using 1:5 with line lw 2 title "S2", \
     inputfile using 1:7 with line lw 2 title "S3"
unset output
