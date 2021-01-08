load 'gnuplot/common.p'
set xlabel 'Trial Number'
set ylabel 'CDR'
set yrange [0:1.1]
plot inputfile using 1:4 with line lt -1 lw 2
unset output
