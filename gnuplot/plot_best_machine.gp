load 'gnuplot/common_adv.gp'
set ylabel 'Best Machine'
set yrange [0:20]
set key right top
plot inputfile using 0:1 with line lw 2 title "M1", \
     inputfile using 0:4 with line lw 2 title "M2", \
     inputfile using 0:7 with line lw 2 title "M3"
unset output
