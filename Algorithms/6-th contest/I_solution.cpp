#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Vertex;
struct Edges {
  int64_t neighbour = 0;
  size_t index;
};

struct Vertex {
  std::vector<Edges> edges;
};

int64_t timer = 0;
std::vector<int64_t> tin;
std::vector<int64_t> ret;
std::set<size_t> answer;

void DFS(std::vector<Vertex>& graph, std::vector<bool>& used, int64_t current,
         int64_t parent) {
  if (used[current]) {
    return;
  }
  timer++;
  tin[current] = timer;
  ret[current] = timer;
  used[current] = true;
  for (auto& u : graph[current].edges) {
    if (u.neighbour == parent) {
      continue;
    }
    if (used[u.neighbour]) {
      ret[current] = std::min(ret[current], tin[u.neighbour]);
    } else {
      DFS(graph, used, u.neighbour, current);
      ret[current] = std::min(ret[current], ret[u.neighbour]);
      if (ret[u.neighbour] > tin[current]) {
        answer.insert(u.index);
      }
    }
  }
}

void FindCutPoint(std::vector<Vertex>& graph) {
  std::vector<bool> used(graph.size(), false);
  for (int64_t i = 0; i < static_cast<int64_t>(graph.size()); ++i) {
    if (!used[i]) {
      DFS(graph, used, i, -1);
    }
  }
}

void Input(std::vector<Vertex>& inp, size_t num_ver, size_t num_path) {
  inp = std::vector<Vertex>(num_ver);
  ret = std::vector<int64_t>(num_ver, 0);
  tin = std::vector<int64_t>(num_ver, 0);
  for (size_t i = 0; i < num_path; ++i) {
    int64_t from = 0;
    int64_t into = 0;
    std::cin >> from >> into;
    inp[from - 1].edges.push_back({into - 1, i + 1});
    inp[into - 1].edges.push_back({from - 1, i + 1});
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t ver_num = 0;
  size_t edge_num = 0;
  std::cin >> ver_num >> edge_num;
  std::vector<Vertex> graph;
  Input(graph, ver_num, edge_num);
  FindCutPoint(graph);
  std::cout << answer.size() << '\n';
  for (const auto& i : answer) {
    std::cout << i << '\n';
  }
  return 0;
}