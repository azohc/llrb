#!/usr/bin/gnuplot

set title "LLRB - Inserción"
set xlabel "Elementos insertados"
set ylabel "Tiempo (ms)"
#set ytics "100"
plot "data"  with lines
pause -1 "Hit any key to continue"