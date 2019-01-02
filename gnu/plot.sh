#!/usr/bin/gnuplot

set title "LLRB - Buscar"
set xlabel "Elementos buscados"
set ylabel "Tiempo (ms)"
#set ytics "100"
plot "data" title "busqueda" with lines
pause -1 "Hit any key to continue"