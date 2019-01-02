#!/usr/bin/gnuplot

set title "plot"
set xlabel "X"
set ylabel "Y"
set ytics "10"
plot "data" title "dataplot" with lines
pause -1 "Hit any key to continue"