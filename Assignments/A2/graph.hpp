#pragma once
#include "randomizer.hpp"
#include <fstream>
#include <unordered_map>
#include <vector>

typedef uint64_t cnt;
typedef uint32_t nid_t;

struct Graph {
  cnt n, m, num_steps, num_walks;
  std::vector<std::vector<nid_t>> adj;
  Randomizer *randomizer;

  // constructor
  Graph(cnt _n, cnt _m, cnt _steps, cnt _walks, Randomizer *_randomizer);

  void construct_graph(
      std::ifstream &file); // construct the graph from the input file
  void rwr(nid_t u);        // perform Random Walk with Restart for node u
};
