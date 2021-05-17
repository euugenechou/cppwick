#!/opt/homebrew/bin/bash

rm -f /tmp/cparser.dat
rm -f /tmp/cppparser.dat
rm -f /tmp/matparser.dat

for f in newicks/*
do
  echo -n "Loading $f across all programs... "

  size=$(stat -f "%z" $f)
  ctime=$(/usr/bin/time -p ./fwparser < $f |& head -n 1 | awk '{ printf $2 }')
  cpptime=$(/usr/bin/time -p ./parser < $f |& head -n 1 | awk '{ printf $2 }')
  mattime=$(/usr/bin/time -p ./newick < $f |& head -n 1 | awk '{ printf $2 }')

  printf "$size $ctime\n" >> /tmp/cparser.dat
  printf "$size $cpptime\n" >> /tmp/cppparser.dat
  printf "$size $mattime\n" >> /tmp/matparser.dat

  echo "done."
done

gnuplot <<XX
set terminal pdf
set tics out nomirror
set key out

set xlabel "File size (bytes)" font ", 10"
set ylabel "Time (seconds)" font ", 10"

set tics font ", 8"

set output "plot.pdf"
set title "Time to Load Newick Tree Format File"
plot "/tmp/cparser.dat" with linespoints pt 7 ps 0 lw 2 lc rgb "blue" title "Flywick (C)", \
	"/tmp/cppparser.dat" with linespoints pt 7 ps 0 lw 2 lc rgb "orange" title "Flywick (C++)", \
	"/tmp/matparser.dat" with linespoints pt 7 ps 0 lw 2 lc rgb "red" title "matUtils"
XX

open plot.pdf
