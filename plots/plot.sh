#! /usr/bin/gnuplot

# set title "tiempo medio de la ejecucion de una operacion"
# set ylabel "tiempo medio (ms)"
# set xlabel "elementos (miles)"
# set ytics 0.0005
# set xtics 20
# plot "opinsert.txt" u 1:2 with lines title "insertar"
# replot "opsearch.txt" u 1:2 with lines title "buscar"
# replot "opdelete.txt" u 1:2 with lines  title "borrar"

set title "tiempo medio de la ejecucion de n operaciones"
set ylabel "tiempo medio (ms)"
set xlabel "elementos (miles)"
set ytics 0.0005
set xtics 20
plot "testinsert.txt" with lines  title "insertar"
replot "testsearch.txt" with lines  title "buscar"
replot "testdelete.txt" with lines  title "borrar"

pause -1