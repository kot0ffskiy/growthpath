#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const size_t kMaxWeight = 30;

struct Vertex {
  size_t name = 0;
  size_t weight = 0;
};

void BFS(std::vector<std::vector<Vertex>>& graph, std::vector<int64_t>& dist,
         size_t vertex) {
  std::vector<std::queue<Vertex>> arr_dist =
      std::vector<std::queue<Vertex>>(kMaxWeight, std::queue<Vertex>());
  arr_dist[0].push({vertex, 0});
  for (size_t i = 0; i < (graph.size() - 1) * kMaxWeight; ++i) {
    while (!arr_dist[i % kMaxWeight].empty()) {
      Vertex current = arr_dist[i % kMaxWeight].front();
      arr_dist[i % kMaxWeight].pop();
      for (auto& u : graph[current.name]) {
        if (dist[u.name] == -1 ||
            dist[u.name] >
                dist[current.name] + static_cast<int64_t>(u.weight)) {
          dist[u.name] = dist[current.name] + static_cast<int64_t>(u.weight);
          arr_dist[dist[u.name % kMaxWeight] % kMaxWeight].push(u);
        }
      }
    }
  }
}

void Input(std::vector<std::vector<Vertex>>& inp, size_t num_ver,
           size_t num_path) {
  inp = std::vector<std::vector<Vertex>>(num_ver, std::vector<Vertex>());
  for (size_t i = 0; i < num_path; ++i) {
    size_t from = 0;
    size_t into = 0;
    size_t weight = 0;
    std::cin >> from >> into >> weight;
    inp[from - 1].push_back({into - 1, weight});
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t ver_num = 0;
  size_t edge_num = 0;
  size_t start = 0;
  size_t finish = 0;
  std::cin >> ver_num >> edge_num >> start >> finish;
  std::vector<std::vector<Vertex>> graph;
  std::vector<int64_t> dist(ver_num, -1);
  Input(graph, ver_num, edge_num);
  BFS(graph, dist, start - 1);
  if (dist[finish - 1] == -1) {
    std::cout << -1 << '\n';
  } else {
    std::cout << dist[finish - 1] + 1 << '\n';
  }
  return 0;
}