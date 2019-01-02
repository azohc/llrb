#!/usr/bin/gnuplot

set title "LLRB - Insertar"
set xlabel "Elementos insertados"
set ylabel "Tiempo (ms)"
#set ytics "100"
plot "data" title "insercion" with lines
pause -1 "Hit any key to continue"