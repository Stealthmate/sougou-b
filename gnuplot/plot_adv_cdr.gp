load 'gnuplot/common_adv.gp'
set ylabel 'CDR'
plot inputfile using 0:3 with line lw 2 title "M1", \
     inputfile using 0:6 with line lw 2 title "M2", \
     inputfile using 0:9 with line lw 2 title "M3"
unset output
