set terminal png size 1000,1000
set datafile separator ","

set output 'k1_plot_engaged_machines.png'
set title 'Engaged Machines'
set xlabel 'Trial number'
set ylabel 'Machine number'
plot 'k1_data.csv' using 1:2

set output 'k1_plot_avg_reward.png'
set title 'Average Reward'
set ylabel 'Average Reward'
plot 'k1_data.csv' using 1:3 with line lt -1 lw 2

set output 'k1_plot_cdr.png'
set title 'CDR'
set ylabel 'CDR'
plot 'k1_data.csv' using 1:4 with line lt -1 lw 2
