load 'gnuplot/common.p'
set xlabel 'Trial number'
set ylabel 'Machine number'
set yrange [0:6]
plot inputfile using 1:2
unset output
