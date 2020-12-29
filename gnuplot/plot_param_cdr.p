set terminal png size 1000,1000
set datafile separator ","

set output outputfile
set title 'CDR'
set xlabel parameter
set ylabel 'CDR'
set yrange [0:1.1]
plot inputfile using 2:4 with line lt -1 lw 2
