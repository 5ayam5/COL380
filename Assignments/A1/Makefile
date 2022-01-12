CC=g++
CFLAGS=-std=c++11 -O2 -fopenmp
DNUM=1009072
THREAD_NUM=4
RUN_NUM=3

sources=main.cpp classify.cpp
objects=$(sources:.cpp=.o)

sources_og=main.cpp classify_og.cpp
objects_og=$(sources_og:.cpp=.o)

classify:$(objects)
	$(CC) $(CFLAGS) $^ -o $@

run: classify
	./classify rfile dfile $(DNUM) $(THREAD_NUM) $(RUN_NUM)

classify_og:$(objects_og)
	$(CC) $(CFLAGS) $^ -o $@

run_og: classify_og
	./classify_og rfile dfile $(DNUM) $(THREAD_NUM) $(RUN_NUM)

%.o: %.cpp classify.h classify_og.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(objects) $(objects_og) classify classify_og gmon.out
