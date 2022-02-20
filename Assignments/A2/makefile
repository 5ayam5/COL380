CC=mpic++
CFLAGS=-std=c++17

NP=4
DATA=data/8717_31525/edges.dat
N=8717
M=31525
RESTART_PROB=0.1
NUM_STEPS=5000
NUM_WALKS=30
NUM_REC=20
SEED=369

sources=main.cpp graph.cpp
objects=$(sources:.cpp=.o)

wtf: $(objects) librandomizer.a
	$(CC) $(CFLAGS) -o $@ $^

run: wtf
	mpirun -np $(NP) ./wtf $(DATA) $(N) $(M) $(RESTART_PROB) $(NUM_STEPS) $(NUM_WALKS) $(NUM_REC) $(SEED)

%.o: %.cpp *.hpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f wtf $(objects)
