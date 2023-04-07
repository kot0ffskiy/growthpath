#include <algorithm>
#include <iostream>
#include <vector>

void DFS(std::vector<std::vector<size_t>>& graph, std::vector<bool>& used,
         std::vector<size_t>& order, size_t vertex) {
  used[vertex] = true;
  for (auto u : graph[vertex]) {
    if (!used[u]) {
      DFS(graph, used, order, u);
    }
  }
  order.push_back(vertex);
}

void ComponentDFS(std::vector<std::vector<size_t>>& transposed_graph,
                  std::vector<size_t>& answer, size_t vertex,
                  size_t component_num) {
  answer[vertex] = component_num;
  for (auto& u : transposed_graph[vertex]) {
    if (answer[u] == 0) {
      ComponentDFS(transposed_graph, answer, u, component_num);
    }
  }
}

void Input(size_t ver_num, size_t edge_num,
           std::vector<std::vector<size_t>>& graph,
           std::vector<std::vector<size_t>>& transposed_graph,
           std::vector<bool>& used) {
  graph = std::vector<std::vector<size_t>>(ver_num, std::vector<size_t>());
  transposed_graph =
      std::vector<std::vector<size_t>>(ver_num, std::vector<size_t>());
  used = std::vector<bool>(ver_num, false);
  for (size_t i = 0; i < edge_num; ++i) {
    size_t first = 0;
    size_t second = 0;
    std::cin >> first >> second;
    graph[first - 1].push_back(second - 1);
    transposed_graph[second - 1].push_back(first - 1);
  }
}

int main() {
  size_t ver_num = 0;
  size_t edge_num = 0;
  std::cin >> ver_num >> edge_num;
  std::vector<std::vector<size_t>> graph;
  std::vector<std::vector<size_t>> transposed_graph;
  std::vector<bool> used;
  Input(ver_num, edge_num, graph, transposed_graph, used);
  std::vector<size_t> order;

  for (size_t v = 0; v < graph.size(); ++v) {
    if (!used[v]) {
      DFS(graph, used, order, v);
    }
  }

  std::vector<size_t> answer(ver_num, 0);
  std::reverse(order.begin(), order.end());
  size_t component_num = 0;
  for (auto& v : order) {
    if (answer[v] == 0) {
      component_num++;
      ComponentDFS(transposed_graph, answer, v, component_num);
    }
  }
  std::cout << component_num << '\n';
  for (const auto& i : answer) {
    std::cout << i << ' ';
  }
  return 0;
}