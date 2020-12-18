set terminal png size 1000,1000
set datafile separator ","

set output outputfile
set title 'Engaged Machines'
set xlabel 'Trial number'
set ylabel 'Machine number'
set yrange [0:6]
plot inputfile using 1:2
