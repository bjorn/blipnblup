qmake -config debug
make clean
make
./blipnblup
gprof blipnblup > gprof.txt
