#include "graph.hpp"
#include "randomizer.hpp"
#include <assert.h>
#include <mpi.h>
#include <string>

int main(int argc, char *argv[]) {
  assert(argc > 8);
  std::string graph_file = argv[1];
  cnt num_nodes = std::stoi(argv[2]);
  cnt num_edges = std::stoi(argv[3]);
  float restart_prob = std::stof(argv[4]);
  cnt num_steps = std::stoi(argv[5]);
  cnt num_walks = std::stoi(argv[6]);
  cnt num_rec = std::stoi(argv[7]);
  int seed = std::stoi(argv[8]);

  // Only one randomizer object should be used per MPI rank, and all should have
  // same seed
  Randomizer random_generator(seed, num_nodes, restart_prob);
  Graph graph(num_nodes, num_edges, num_steps, num_walks, &random_generator);
  int rank, size;

  // Starting MPI pipeline
  MPI_Init(NULL, NULL);

  // Extracting Rank and Processor Count
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank != 0 || rank == size - 1) {
    std::ifstream file(graph_file, std::ios::binary);
    if (file.is_open())
      graph.construct_graph(file);
    else {
      std::cout << "Error: could not open file.\n";
      MPI_Finalize();
      return 0;
    }
  }

  if (rank == size - 1) {
    for (nid_t i = 0; i < num_nodes; i++)
      graph.rwr(i);
  }

  MPI_Finalize();
}
