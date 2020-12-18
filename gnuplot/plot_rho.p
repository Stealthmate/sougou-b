set terminal png size 1000,1000
set datafile separator ","

set output outputfile
set title 'Rho'
set ylabel 'Rho'
set xlabel 'Trial Number'
set yrange[0:1.1]
plot inputfile using 1:5 with line lw 2, \
     inputfile using 1:6 with line lw 2, \
     inputfile using 1:7 with line lw 2, \
     inputfile using 1:8 with line lw 2, \
     inputfile using 1:9 with line lw 2, \