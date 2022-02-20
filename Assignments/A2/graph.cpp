#include "graph.hpp"

Graph::Graph(cnt _n, cnt _m, cnt _steps, cnt _walks, Randomizer *_randomizer) {
  this->n = _n;
  this->m = _m;
  this->num_steps = _steps;
  this->num_walks = _walks;
  this->randomizer = _randomizer;
  this->adj.assign(n, std::vector<nid_t>());
}

bool get_endianness() {
  int num = 1;
  return *(char *)&num == 1;
}

void read_nid(nid_t &n, std::ifstream &file, bool little) {
  if (little) {
    unsigned char buffer[4];
    file.read((char *)buffer, sizeof(buffer));
    n = (int)buffer[3] | (int)buffer[2] << 8 | (int)buffer[1] << 16 |
        (int)buffer[0] << 24;
  } else
    file.read((char *)&n, sizeof(n));
}

void Graph::construct_graph(std::ifstream &file) {
  nid_t u, v;
  bool is_little = get_endianness();
  for (cnt i = 0; i < m; i++) {
    read_nid(u, file, is_little);
    read_nid(v, file, is_little);
    adj[u].push_back(v);
  }
}

void Graph::rwr(nid_t u) {
  std::unordered_map<nid_t, cnt> scores;

  auto walk = [&](nid_t v, cnt walks, cnt steps) {
    while (walks--)
      while (steps--) {
        auto &vec = this->adj[v];
        if (vec.empty())
          break;
        int val = this->randomizer->get_random_value(u);
        if (val < 0)
          break;
        v = vec[val % vec.size()];
        scores[v]++;
      }
  };

  for (auto v : this->adj[u])
    walk(v, this->num_walks, this->num_steps);
}
