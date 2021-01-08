load 'gnuplot/common.p'
set xlabel 'Trial number'
set ylabel 'AverageReward'
set yrange [0:1.1]
plot inputfile using 1:3 with line lt -1 lw 2
   unset output
