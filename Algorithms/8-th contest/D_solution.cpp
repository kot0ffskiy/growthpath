#include <algorithm>
#include <iostream>
#include <set>
#include <stack>
#include <vector>

class DisjointSet {
 public:
  DisjointSet(int n) {
    for (int i = 0; i < n; i++) {
      root_indices_.push_back(i);
    }
  }

  int find(int x) {
    if (root_indices_[x] == x) {
      return x;
    }
    return root_indices_[x] = find(root_indices_[x]);
  }

  void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
      root_indices_[y] = x;
    }
  }

  bool are_same(int x, int y) { return find(x) == find(y); }

 private:
  std::vector<int> root_indices_;
};

bool IsAsk(std::string& input) { return input == "ask"; }

int main() {
  int vertex_count = 0;
  std::cin >> vertex_count;
  vertex_count++;
  std::vector<std::pair<int, std::pair<int, int>>> graph;

  for (int i = 0; i < vertex_count; i++) {
    for (int j = 0; j < vertex_count - 1; j++) {
      int weight = 0;
      std::cin >> weight;
      graph.push_back({weight, {i, j}});
    }
  }
  std::sort(graph.begin(), graph.end());
  DisjointSet dsu(vertex_count);
  int answer = 0;

  for (const auto& item : graph) {
    int weight = item.first;
    int first_vertex = item.second.first;
    int second_vertex = item.second.second;

    if (!dsu.are_same(first_vertex, second_vertex)) {
      answer += weight;
      dsu.unite(first_vertex, second_vertex);
    }
  }

  std::cout << answer;
  return 0;
}