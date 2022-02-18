#include "randomizer.hpp"
#include <assert.h>
#include <mpi.h>
#include <string>

// Notice how the randomizer is being used in this dummy function
void print_random(int tid, int num_nodes, Randomizer r) {
  int this_id = tid;
  int num_steps = 10;
  int num_child = 20;

  std::string s = "Thread " + std::to_string(this_id) + "\n";
  std::cout << s;

  for (int i = 0; i < num_nodes; i++) {
    // Processing one node
    for (int j = 0; j < num_steps; j++) {
      if (num_child > 0) {
        // Called only once in each step of random walk using the original node
        // id for which we are calculating the recommendations
        int next_step = r.get_random_value(i);
        // Random number indicates restart
        if (next_step < 0) {
          std::cout << "Restart \n";
        } else {
          // Deciding next step based on the output of randomizer which was
          // already called
          int child =
              next_step % 20; // 20 is the number of child of the current node
          std::string s = "Thread " + std::to_string(this_id) + " rand " +
                          std::to_string(child) + "\n";
          std::cout << s;
        }
      } else {
        std::cout << "Restart \n";
      }
    }
  }
}

int main(int argc, char *argv[]) {
  assert(argc > 8);
  std::string graph_file = argv[1];
  int num_nodes = std::stoi(argv[2]);
  int num_edges = std::stoi(argv[3]);
  float restart_prob = std::stof(argv[4]);
  int num_steps = std::stoi(argv[5]);
  int num_walks = std::stoi(argv[6]);
  int num_rec = std::stoi(argv[7]);
  int seed = std::stoi(argv[8]);

  // Only one randomizer object should be used per MPI rank, and all should have
  // same seed
  Randomizer random_generator(seed, num_nodes, restart_prob);
  int rank, size;

  // Starting MPI pipeline
  MPI_Init(NULL, NULL);

  // Extracting Rank and Processor Count
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  print_random(rank, num_nodes, random_generator);

  MPI_Finalize();
}
