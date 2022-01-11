CC=g++
CFLAGS=-std=c++11 -O2

sources=main.cpp classify.cpp
objects=$(sources:.cpp=.o)

sources_og=main.cpp classify_og.cpp
objects_og=$(sources_og:.cpp=.o)

classify:$(objects)
	$(CC) $(CFLAGS) -fopenmp $^ -o $@

run: classify
	./classify rfile dfile 1009072 4 25

classify_og:$(objects_og)
	$(CC) $(CFLAGS) -fopenmp $^ -o $@

run_og: classify_og
	./classify_og rfile dfile 1009072 4 25

%.o: %.cpp classify.h classify_og.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(objects) $(objects_og) classify classify_og gmon.out
