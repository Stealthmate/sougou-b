load 'gnuplot/common.gp'
set xlabel 'Trial number'
set ylabel 'Average Reward'
set yrange [0:1.1]
plot inputfile using 1:2 with line lw 2 title "S1", \
     inputfile using 1:4 with line lw 2 title "S2", \
     inputfile using 1:6 with line lw 2 title "S3"
unset output
