#! /usr/bin/gnuplot

set title "media del tiempo transcurrido durante la ejecucion de una operacion"
set ylabel "tiempo promedio (ms)"
set xlabel "elementos (miles)"
set ytics 0.0005
set xtics 250
plot "opinsert.txt" u 1:2 with lines title "insertar"
replot "opsearch.txt" u 1:2 with lines title "buscar"
replot "opdelete.txt" u 1:2 with lines  title "borrar"

# set title "media del tiempo transcurrido durante la ejecucion de 'e' operaciones"
# set ylabel "tiempo promedio (ms)"
# set xlabel "elementos (miles)"
# set xtics 500
# set ytics 25
# plot "testinsert.txt" with lines  title "insertar"
# replot "testsearch.txt" with lines  title "buscar"
# replot "testdelete.txt" with lines  title "borrar"

pause -1