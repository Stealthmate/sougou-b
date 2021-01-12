load 'gnuplot/common.p'
set xlabel 'Simulation Number'
set ylabel 'CDR'
set yrange [-0.1:1.2]
set xrange [0:100]
plot 'data/kadv-1-1.csv' using 0:3 with line lw 2 title "M1", \
     'data/kadv-1-2.csv' using 0:3 with line lw 2 title "M2", \
     'data/kadv-1-3.csv' using 0:3 with line lw 2 title "M3"
unset output
