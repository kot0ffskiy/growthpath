#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

enum Color { White, Grey, Black };

bool cycle_found = false;

std::stack<size_t> path;

void DFS(std::vector<Color>& color, std::vector<std::vector<size_t>>& graph,
         size_t vertex) {
  color[vertex] = Grey;
  if (cycle_found) {
    return;
  }
  path.push(vertex);
  for (auto& u : graph[vertex]) {
    if (color[u] == White) {
      DFS(color, graph, u);
    }
    if (cycle_found) {
      return;
    }
    if (color[u] == Grey) {
      // found
      path.push(u);  // path.top() -- первая вершина цикла
      cycle_found = true;
      return;
    }
  }
  color[vertex] = Black;
  path.pop();
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

void Print() {
  size_t start = path.top();
  path.pop();
  std::vector<size_t> answer;
  while (path.top() != start) {
    answer.push_back(path.top() + 1);
    path.pop();
  }
  answer.push_back(start + 1);
  std::reverse(answer.begin(), answer.end());
  std::cout << "YES\n";
  for (auto i : answer) {
    std::cout << i << ' ';
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
    Print();
  } else {
    std::cout << "NO\n";
  }
  return 0;
}