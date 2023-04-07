#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

enum Color { White, Grey, Black };

bool cycle_found = false;

void DFS(std::vector<Color>& color, std::vector<std::vector<size_t>>& graph,
         size_t vertex) {
  color[vertex] = Grey;
  if (cycle_found) {
    return;
  }
  for (auto& u : graph[vertex]) {
    if (color[u] == White) {
      DFS(color, graph, u);
    }
    if (cycle_found) {
      return;
    }
    if (color[u] == Grey) {
      // found
      cycle_found = true;
      return;
    }
  }
  color[vertex] = Black;
}

void Input(std::vector<Color>& color, std::vector<std::vector<size_t>>& inp,
           size_t num_ver, size_t num_path) {
  inp = std::vector<std::vector<size_t>>(num_ver, std::vector<size_t>());
  color = std::vector<Color>(num_ver, White);
  for (size_t i = 0; i < num_path; ++i) {
    size_t from = 0;
    size_t into = 0;
    std::cin >> from >> into;
    inp[from - 1].push_back(into - 1);
  }
}

void Topsort(std::vector<std::vector<size_t>>& graph, std::vector<bool>& used,
             std::stack<size_t>& answer, size_t vertex) {
  used[vertex] = true;
  for (const auto& u : graph[vertex]) {
    if (!used[u]) {
      Topsort(graph, used, answer, u);
    }
  }
  answer.push(vertex);
}

void Print(std::stack<size_t>& answer) {
  while (!answer.empty()) {
    std::cout << answer.top() + 1 << ' ';
    answer.pop();
  }
}

int main() {
  size_t ver = 0;
  size_t roads = 0;
  std::cin >> ver >> roads;
  // MakeGraph
  std::vector<std::vector<size_t>> graph;
  std::vector<Color> color;
  Input(color, graph, ver, roads);
  for (size_t vertex = 0; vertex < graph.size(); ++vertex) {
    if (color[vertex] == White) {
      DFS(color, graph, vertex);
    }
  }
  if (cycle_found) {
    std::cout << -1;
    return 0;
  }
  std::vector<bool> used(ver, false);
  std::stack<size_t> answer;
  for (size_t i = 0; i < ver; ++i) {
    if (!used[i]) {
      Topsort(graph, used, answer, i);
    }
  }
  Print(answer);
  return 0;
}