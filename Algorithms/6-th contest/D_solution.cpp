#include <iostream>
#include <vector>

void DFS(std::vector<std::vector<size_t>>& graph, std::vector<bool>& used,
         std::vector<size_t>& answer, size_t vertex) {
  answer.push_back(vertex);
  used[vertex] = true;
  for (auto u : graph[vertex]) {
    if (!used[u]) {
      DFS(graph, used, answer, u);
    }
  }
}

void Input(size_t clons_num, size_t pairs_num,
           std::vector<std::vector<size_t>>& graph, std::vector<bool>& used) {
  graph = std::vector<std::vector<size_t>>(clons_num, std::vector<size_t>());
  used = std::vector<bool>(clons_num, false);
  for (size_t i = 0; i < pairs_num; ++i) {
    size_t first = 0;
    size_t second = 0;
    std::cin >> first >> second;
    graph[first - 1].push_back(second - 1);
    graph[second - 1].push_back(first - 1);
  }
}

void Print(std::vector<std::vector<size_t>>& answer) {
  std::cout << answer.size() << '\n';
  for (const auto& i : answer) {
    std::cout << i.size() << '\n';
    for (const auto& j : i) {
      std::cout << j + 1 << ' ';
    }
    std::cout << '\n';
  }
}

int main() {
  size_t clons_num = 0;
  size_t pairs_num = 0;
  std::cin >> clons_num >> pairs_num;
  std::vector<std::vector<size_t>> graph;
  std::vector<bool> used;
  Input(clons_num, pairs_num, graph, used);
  std::vector<std::vector<size_t>> answer;
  for (size_t v = 0; v < graph.size(); ++v) {
    if (!used[v]) {
      std::vector<size_t> tmp;
      DFS(graph, used, tmp, v);
      answer.push_back(tmp);
    }
  }
  Print(answer);
  return 0;
}