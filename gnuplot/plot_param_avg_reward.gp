load 'gnuplot/common.gp'
set xlabel parameter
set xtics 0,0.2,1
set ylabel 'Average Reward'
set yrange [0:1.1]
plot inputfile using 2:3 with line lt -1 lw 2
