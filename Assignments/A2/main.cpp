#include "graph.hpp"
#include "randomizer.hpp"
#include <assert.h>
#include <chrono>
#include <mpi.h>
#include <string>

int main(int argc, char *argv[]) {
  assert(argc == 9 || argc == 10);
  std::string graph_file = argv[1];
  cnt num_nodes = std::stoi(argv[2]);
  cnt num_edges = std::stoi(argv[3]);
  float restart_prob = std::stof(argv[4]);
  cnt num_steps = std::stoi(argv[5]);
  cnt num_walks = std::stoi(argv[6]);
  cnt num_rec = std::stoi(argv[7]);
  int seed = std::stoi(argv[8]);
  std::string outfile = "output.dat";
  if (argc == 10)
    outfile = argv[9];

  // Only one randomizer object should be used per MPI rank, and all should have
  // same seed
  Randomizer random_generator(seed, num_nodes, restart_prob);
  Graph graph(num_nodes, num_edges, num_steps, num_walks, num_rec,
              &random_generator, outfile);
  int rank, size;

  auto begin = std::chrono::high_resolution_clock::now();

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

  if (size == 1) {
    for (nid_t i = 0; i < num_nodes; i++)
      graph.rwr(i);
    graph.out->close();
    MPI_Finalize();
    if (rank == 0) {
      auto end = std::chrono::high_resolution_clock::now();
      double duration =
          (1e-6 *
           (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin))
               .count());
      std::cout << "Time taken: " << duration << "ms" << '\n';
    }
    return 0;
  }

  MPI_Status status;
  if (rank == 0) { // master rank which schedules tasks
    int r_id;
    for (nid_t i = 0; i < num_nodes; i++) {
      MPI_Recv(&r_id, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
      MPI_Send(&i, 1, MPI_INT, r_id, 0, MPI_COMM_WORLD);
    }
    int node = -1;
    for (int i = 1; i < size; i++) {
      MPI_Recv(&r_id, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
      MPI_Send(&node, 1, MPI_INT, r_id, 0, MPI_COMM_WORLD);
    }
  } else {
    int node;
    while (true) {
      MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
      MPI_Recv(&node, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
      if (node == -1)
        break;
      graph.rwr(node);
    }
    graph.out->close();
  }

  MPI_Finalize();
  if (rank == 0) {
    auto end = std::chrono::high_resolution_clock::now();
    double duration =
        (1e-6 *
         (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin))
             .count());
    std::cout << "Time taken: " << duration << "ms" << '\n';
  }
  return 0;
}
