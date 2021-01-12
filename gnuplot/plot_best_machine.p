load 'gnuplot/common.p'
set xlabel 'Simulation Number'
set ylabel 'Best Machine'
set yrange [0:20]
set xrange [0:100]
plot 'data/kadv-1-1.csv' using 0:1 title "M1", \
     'data/kadv-1-2.csv' using 0:1 title "M2", \
     'data/kadv-1-3.csv' using 0:1 title "M3"
unset output
