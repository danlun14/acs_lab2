set terminal png size 1000, 450 font 'Verdana, 10'
set output 'OpType_O2.png' 
set title "Operand type impact (-O2)"
set xlabel 'LNum'
set ylabel 'TaskPerf'
set xzeroaxis lt -1
set yzeroaxis lt -1
set key left top

set grid xtics lc rgb  '#555555' lw 1 lt 0
set grid ytics lc rgb  '#555555' lw 1 lt 0

set xtics axis
set ytics axis
plot 'int2.txt' using 1:2 with linespoints lw 1 lt rgb 'blue' title 'Int number perfomance', \
 'float2.txt' using 1:2 with linespoints lw 1 lt rgb 'red' title 'Float number perfomance', \
 'double2.txt' using 1:2 with linespoints lw 1 lt rgb 'purple' title 'Double number perfomance'