#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

int64_t timer = 0;
std::vector<int64_t> tin;
std::vector<int64_t> ret;
std::set<int64_t> answer;

void DFS(std::vector<std::set<int64_t>>& graph, std::vector<bool>& used,
         int64_t parent, int64_t current) {
  if (used[current]) {
    return;
  }
  timer++;
  tin[current] = timer;
  ret[current] = timer;
  used[current] = true;
  int64_t counter = 0;
  for (auto& u : graph[current]) {
    if (u == parent) {
      continue;
    }
    if (used[u]) {
      ret[current] = std::min(ret[current], tin[u]);
    } else {
      DFS(graph, used, current, u);
      counter++;
      ret[current] = std::min(ret[current], ret[u]);
      if (parent != -1 && ret[u] >= tin[current]) {
        answer.insert(current);
      }
    }
  }
  if (parent == -1 && counter >= 2) {
    answer.insert(current);
  }
}

void FindCutPoint(std::vector<std::set<int64_t>>& graph) {
  std::vector<bool> used(graph.size(), false);
  for (int64_t i = 0; i < static_cast<int64_t>(graph.size()); ++i) {
    if (!used[i]) {
      DFS(graph, used, -1, i);
    }
  }
}

void Input(std::vector<std::set<int64_t>>& inp, int64_t num_ver,
           int64_t num_path) {
  inp = std::vector<std::set<int64_t>>(num_ver, std::set<int64_t>());
  ret = std::vector<int64_t>(num_ver, 0);
  tin = std::vector<int64_t>(num_ver, 0);
  for (int64_t i = 0; i < num_path; ++i) {
    int64_t from = 0;
    int64_t into = 0;
    std::cin >> from >> into;
    inp[from - 1].insert(into - 1);
    inp[into - 1].insert(from - 1);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t ver_num = 0;
  int64_t edge_num = 0;
  std::cin >> ver_num >> edge_num;
  std::vector<std::set<int64_t>> graph;
  Input(graph, ver_num, edge_num);
  FindCutPoint(graph);
  std::cout << answer.size() << '\n';
  for (const auto& i : answer) {
    std::cout << i + 1 << '\n';
  }
  return 0;
}