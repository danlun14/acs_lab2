set terminal png size 1000, 450 font 'Verdana, 10'
set output 'Optimization_INT.png' 
set title "Optimization impact"
set xlabel 'LNum'
set ylabel 'TaskPerf'
set xzeroaxis lt -1
set yzeroaxis lt -1
set key left top

set grid xtics lc rgb  '#555555' lw 1 lt 0
set grid ytics lc rgb  '#555555' lw 1 lt 0

set xtics axis
set ytics axis
plot 'Opt0.txt' using 1:2 with linespoints lw 1 lt rgb 'blue' title 'Optimization O0', \
 'Opt1.txt' using 1:2 with linespoints lw 1 lt rgb 'red' title 'Optimization O1', \
 'Opt2.txt' using 1:2 with linespoints lw 1 lt rgb 'purple' title 'Optimization O2', \
 'Opt3.txt' using 1:2 with linespoints lw 1 lt rgb 'black' title 'Optimization O3'