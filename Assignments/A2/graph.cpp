#include "graph.hpp"

Graph::Graph(cnt _n, cnt _m, cnt _steps, cnt _walks, cnt _recs,
             Randomizer *_randomizer, std::string outfile) {
  this->n = _n;
  this->m = _m;
  this->num_steps = _steps;
  this->num_walks = _walks;
  this->num_recs = _recs;
  this->randomizer = _randomizer;
  this->adj.assign(n, std::vector<nid_t>());
  this->neighbours.assign(n, std::unordered_set<nid_t>());
  this->out = new std::ofstream(outfile, std::ios::binary);
}

void read_nid(nid_t &n, std::ifstream &file) {
  unsigned char buffer[4];
  file.read((char *)buffer, sizeof(buffer));
  n = (int)buffer[3] | (int)buffer[2] << 8 | (int)buffer[1] << 16 |
      (int)buffer[0] << 24;
}

void write_val(nid_t n, std::ofstream *file) {
  uint offset = sizeof(n) * 8;
  char buffer;
  do {
    offset -= 8;
    buffer = (n >> offset) & 0xFF;
    file->write(&buffer, sizeof(buffer));
  } while (offset != 0);
}

void Graph::construct_graph(std::ifstream &file) {
  nid_t u, v;
  for (cnt i = 0; i < m; i++) {
    read_nid(u, file);
    read_nid(v, file);
    this->adj[u].push_back(v);
    this->neighbours[u].insert(v);
  }
  file.close();
}

void Graph::rwr(nid_t u) {
  std::unordered_map<nid_t, cnt> scores;

  auto walk = [&](nid_t v, nid_t w, cnt walks, cnt steps) {
    while (walks--) {
      w = v;
      cnt curr_steps = steps;
      while (curr_steps--) {
        auto &vec = this->adj[w];
        if (vec.empty()) {
          w = v;
          continue;
        }
        int val = this->randomizer->get_random_value(u);
        if (val < 0) {
          w = v;
          continue;
        }
        w = vec[val % vec.size()];
        if (w != u && !this->neighbours[u].count(w))
          scores[w]++;
      }
    }
  };

  for (auto v : this->adj[u])
    walk(v, v, this->num_walks, this->num_steps);

  std::vector<std::pair<cnt, nid_t>> recommendations;
  for (auto p : scores)
    recommendations.push_back({p.second, p.first});
  std::sort(recommendations.begin(), recommendations.end(),
            [](const std::pair<cnt, nid_t> &a, const std::pair<cnt, nid_t> &b) {
              if (a.first == b.first)
                return a.second < b.second;
              return a.first > b.first;
            });

  this->out->seekp(u * (2 * this->num_recs + 1) * sizeof(u));
  write_val(this->adj[u].size(), this->out);
  for (cnt i = 0; i < std::min(recommendations.size(), this->num_recs); i++) {
    write_val(recommendations[i].second, this->out);
    write_val(recommendations[i].first, this->out);
  }
  char buffer[4];
  buffer[0] = 'N', buffer[1] = 'U', buffer[2] = 'L', buffer[3] = 'L';
  for (cnt i = std::min(recommendations.size(), this->num_recs);
       i < this->num_recs; i++) {
    this->out->write(buffer, sizeof(buffer));
    this->out->write(buffer, sizeof(buffer));
  }
}

Graph::~Graph() { free(this->out); }
