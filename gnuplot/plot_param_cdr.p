load 'gnuplot/common.p'
set xlabel parameter
set xtics 0,0.2,1
set ylabel 'CDR'
set yrange [0:1.1]
plot inputfile using 2:4 with line lt -1 lw 2
