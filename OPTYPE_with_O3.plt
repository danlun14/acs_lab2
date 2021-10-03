set terminal png size 1000, 450 font 'Verdana, 10'
set output 'OpType_O3.png' 
set title "Operand type impact (-O3)"
set xlabel 'LNum'
set ylabel 'TaskPerf'
set xzeroaxis lt -1
set yzeroaxis lt -1
set key left top

set grid xtics lc rgb  '#555555' lw 1 lt 0
set grid ytics lc rgb  '#555555' lw 1 lt 0

set xtics axis
set ytics axis
plot 'int3.txt' using 1:2 with linespoints lw 1 lt rgb 'blue' title 'Int number perfomance', \
 'float3.txt' using 1:2 with linespoints lw 1 lt rgb 'red' title 'Float number perfomance', \
 'double3.txt' using 1:2 with linespoints lw 1 lt rgb 'purple' title 'Double number perfomance'