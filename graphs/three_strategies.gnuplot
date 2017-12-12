set terminal postscript eps enhanced color
set output  'three_strategies.eps'
set xlabel  'Number of pop+push swap steps' font "Helvetica,14"
set ylabel  'Time (milli-seconds)' font "Helvetica,14"

set size 1,0.75
set xrange  [0:]
set yrange  [0:]
set style line 11 lc rgb "#AAAAAA" lt 1
set border 3 back ls 11
set tics nomirror
set style line 12 lc rgb "#AAAAAA" lt 0 lw 1
set grid back ls 12
set key top left
set key font "Helvetica,14"
#set key spacing 0.7
set xtics format '%.0s%c'
set xtics  font "Helvetica,14"
set ytics  font "Helvetica,14"
plot 'three_strategies.data.clang' using 1:2 with linespoints pt 7 ps 0.75 lw 2.5 lc rgb "orange"   title 'Clang max\_element()', 'three_strategies.data.gcc'   using 1:2 with linespoints pt 7 ps 0.75 lw 2.5 lc rgb "purple"   title 'GCC   max\_element()', 'three_strategies.data.clang' using 1:4 with linespoints pt 5 ps 0.60 lw 2.5 lc rgb "blue"     title 'Clang sort()', 'three_strategies.data.gcc'   using 1:4 with linespoints pt 5 ps 0.60 lw 2.5 lc rgb "pink"     title 'GCC   sort()', 'three_strategies.data.clang' using 1:3 with linespoints pt 5 ps 0.60 lw 2.5 lc rgb "green"    title 'Clang heap', 'three_strategies.data.gcc'   using 1:3 with linespoints pt 5 ps 0.60 lw 2.5 lc rgb "red"      title 'GCC   heap'