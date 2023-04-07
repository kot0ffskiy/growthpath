#include <algorithm>
#include <iostream>
#include <vector>

size_t MinDFS(std::vector<std::vector<std::pair<size_t, size_t>>>& graph,
              size_t anchestor, size_t tofind, size_t current, size_t weight) {
  for (auto& vertex : graph[current]) {
    if (current == tofind) {
      return size_t() - 1;
    }
    if (vertex.first != anchestor) {
      size_t func = MinDFS(graph, current, tofind, vertex.first, weight);
      if (func != 0) {
        return std::min(func, vertex.second);
      }
    }
  }
  return size_t();
}

class DisjointSet {
 public:
  explicit DisjointSet(size_t vertex_count) {
    for (size_t i = 0; i < vertex_count; i++) {
      root_indices_.push_back(i);
    }
  }

  void Unite(size_t x, size_t y) {
    x = Find(x);
    y = Find(y);
    if (x != y) {
      root_indices_[y] = x;
    }
  }

  bool AreSame(size_t x, size_t y) { return Find(x) == Find(y); }

 private:
  std::vector<size_t> root_indices_;
  size_t Find(size_t x) {
    if (root_indices_[x] == x) {
      return x;
    }
    return root_indices_[x] = Find(root_indices_[x]);
  }
};

int main() {
  size_t vertex_count = 0;
  size_t edges_count = 0;
  size_t query_count = 0;
  std::cin >> vertex_count >> edges_count >> query_count;
  std::vector<std::pair<size_t, std::pair<size_t, size_t>>> graph;

  for (size_t i = 0; i < edges_count; i++) {
    size_t first_vertex = 0;
    size_t second_vertex = 0;
    size_t weight = 0;
    std::cin >> first_vertex >> second_vertex >> weight;
    graph.push_back({weight, {first_vertex - 1, second_vertex - 1}});
  }

  std::sort(graph.begin(), graph.end(), std::greater<>());
  DisjointSet dsu(vertex_count);
  std::vector<std::pair<size_t, std::pair<size_t, size_t>>> max_span;
  for (const auto& item : graph) {
    size_t first_vertex = item.second.first;
    size_t second_vertex = item.second.second;

    if (!dsu.AreSame(first_vertex, second_vertex)) {
      max_span.push_back(item);
      dsu.Unite(first_vertex, second_vertex);
    }
  }

  std::vector<std::vector<std::pair<size_t, size_t>>> new_graph(vertex_count);
  for (const auto& item : max_span) {
    size_t first_vertex = item.second.first;
    size_t second_vertex = item.second.second;
    size_t weight = item.first;
    new_graph[first_vertex].emplace_back(second_vertex, weight);
    new_graph[second_vertex].emplace_back(first_vertex, weight);
  }
  // query
  for (size_t i = 0; i < query_count; ++i) {
    size_t first_vertex = 0;
    size_t second_vertex = 0;
    std::cin >> first_vertex >> second_vertex;
    std::cout << MinDFS(new_graph, -1, first_vertex - 1, second_vertex - 1, -1)
              << '\n';
  }

  return 0;
}