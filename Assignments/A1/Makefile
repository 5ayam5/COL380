libsort.so: psort.cpp psort.h
	g++ -fPIC -g -c -Wall psort.cpp -fopenmp
	g++ -shared -Wl,-soname,libsort.so -o libsort.so psort.o

driver: driver.cpp libsort.so
	g++ -L. -fopenmp -g driver.cpp -o driver -lsort 

run: driver
	LD_LIBRARY_PATH=. ./driver $(input) $(num_threads)

cachegrind: driver FORCE
	export LD_LIBRARY_PATH=.
	valgrind --tool=cachegrind --cachegrind-out-file=cachegrind.out ./driver $(input) $(num_threads)

FORCE: ;

clean:
	rm -f *.so *.o driver
