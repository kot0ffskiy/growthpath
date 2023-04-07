#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int64_t current = 0;
  int64_t neighbour = 0;
  int64_t weight = 0;
};

const int64_t kInf = 1e13;
const int64_t kMiss = 1e5;

void PrintAns(std::vector<int64_t>& path, int64_t flag) {
  if (flag == -1) {
    std::cout << "NO";
  } else {
    std::vector<int64_t> answer;
    int64_t rem = flag;
    for (int64_t k = 0; k < static_cast<int64_t>(path.size()); ++k) {
      rem = path[rem];
    }
    int64_t current = rem;
    answer.push_back(current);
    while (current != rem || answer.size() == 1) {
      current = path[current];
      answer.push_back(current);
    }
    std::reverse(answer.begin(), answer.end());
    std::cout << "YES\n" << answer.size() << '\n';
    for (auto& item : answer) {
      std::cout << item + 1 << ' ';
    }
  }
}

void FordBellman(std::vector<Edge>& graph, std::vector<int64_t>& dist,
                 std::vector<int64_t>& path, int64_t ver_num) {
  dist[0] = 0;
  int64_t last_iter = -1;
  for (int64_t k = 0; k < ver_num; ++k) {
    last_iter = -1;
    for (auto& j : graph) {
      if (dist[j.neighbour] > (dist[j.current] + j.weight)) {
        dist[j.neighbour] = dist[j.current] + j.weight;
        path[j.neighbour] = j.current;
        last_iter = j.neighbour;
      }
    }
  }
  PrintAns(path, last_iter);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t ver_num = 0;
  std::cin >> ver_num;
  std::vector<Edge> graph(ver_num * ver_num);
  std::vector<int64_t> dist(ver_num + 1, kInf);
  std::vector<int64_t> path(ver_num + 1, -1);
  int64_t graph_iter = 0;
  for (int64_t i = 0; i < ver_num; ++i) {
    for (int64_t k = 0; k < ver_num; ++k) {
      int64_t weight = 0;
      std::cin >> weight;
      if (weight != kMiss) {
        graph[graph_iter++] = {i, k, weight};
      }
    }
  }
  FordBellman(graph, dist, path, ver_num);
  return 0;
}