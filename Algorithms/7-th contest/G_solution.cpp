#include <algorithm>
#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<int64_t>>;

Matrix& MakeTransitive(Matrix& graph) {
  for (size_t i = 0; i < graph.size(); ++i) {
    for (size_t v = 0; v < graph.size(); ++v) {
      for (size_t u = 0; u < graph.size(); ++u) {
        if (graph[v][i] != 0 && graph[i][u] != 0) {
          graph[v][u] = 1;
        }
      }
    }
  }
  return graph;
}

int main() {
  int64_t rooms = 0;
  std::cin >> rooms;
  Matrix graph(rooms, std::vector<int64_t>(rooms));
  for (auto& i : graph) {
    for (auto& j : i) {
      std::cin >> j;
    }
  }
  MakeTransitive(graph);
  for (auto& i : graph) {
    for (auto& j : i) {
      std::cout << j << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}