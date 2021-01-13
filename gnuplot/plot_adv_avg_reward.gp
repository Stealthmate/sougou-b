load 'gnuplot/common_adv.gp'
set ylabel 'Average Reward'
plot inputfile using 0:2 with line lw 2 title "M1", \
     inputfile using 0:5 with line lw 2 title "M2", \
     inputfile using 0:8 with line lw 2 title "M3"
unset output
