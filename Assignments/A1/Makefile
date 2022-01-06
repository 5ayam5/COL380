CC=g++
CFLAGS=-std=c++11 -O2

sources=main.cpp classify.cpp
objects=$(sources:.cpp=.o)

classify:$(objects)
	$(CC) $(CFLAGS) -fopenmp $^ -o $@

run: classify
	./classify rfile dfile 1009072 4 3

%.o: %.cpp classify.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o classify
