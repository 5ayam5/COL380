libsort.so: psort.cpp psort.h
	g++ -fPIC -g -c -Wall psort.cpp -fopenmp
	g++ -shared -Wl,-soname,libsort.so -o libsort.so psort.o -lc

run: driver
	./driver input.txt $(num_threads)

driver: driver.cpp libsort.so
	g++ -L. -lsort -fopenmp -g psort.o driver.cpp -o driver

cachegrind: driver FORCE
	valgrind --tool=cachegrind --cachegrind-out-file=cachegrind.out ./driver $(input) $(num_threads)

FORCE: ;

clean:
	rm -f *.so *.o driver
