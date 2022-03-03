#pragma once
#include "randomizer.hpp"
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef uint64_t cnt;
typedef uint32_t nid_t;

struct Graph {
  cnt n, m, num_steps, num_walks, num_recs;
  std::vector<std::vector<nid_t>> adj;
  std::vector<std::unordered_set<nid_t>> neighbours;
  Randomizer *randomizer;
  std::ofstream *out;

  // constructor
  Graph(cnt _n, cnt _m, cnt _steps, cnt _walks, cnt _recs,
        Randomizer *_randomizer, std::string outfile = "output.dat");
  ~Graph();

  void construct_graph(
      std::ifstream &file); // construct the graph from the input file
  void rwr(nid_t u);        // perform Random Walk with Restart for node u
};
