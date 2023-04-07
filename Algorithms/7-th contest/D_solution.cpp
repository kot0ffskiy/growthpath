#include <iostream>
#include <vector>

struct Edge {
  int64_t current = 0;
  int64_t neighbour = 0;
  int64_t weight = 0;
};

// infinity constant
const int64_t kInf = 30000;

std::vector<int64_t>& FordBellman(std::vector<Edge>& graph,
                                  std::vector<int64_t>& answer,
                                  int64_t ver_num) {
  answer[0] = 0;
  for (int64_t k = 0; k < ver_num - 1; ++k) {
    for (auto& j : graph) {
      if (answer[j.current] < kInf) {
        answer[j.neighbour] =
            std::min(answer[j.neighbour], answer[j.current] + j.weight);
      }
    }
  }
  return answer;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t ver_num = 0;
  int64_t edge_num = 0;
  std::cin >> ver_num >> edge_num;
  std::vector<Edge> graph(edge_num);
  std::vector<int64_t> answer(ver_num, kInf);
  for (auto& edge : graph) {
    int64_t from = 0;
    int64_t into = 0;
    int64_t weight = 0;
    std::cin >> from >> into >> weight;
    edge.current = from - 1;
    edge.neighbour = into - 1;
    edge.weight = weight;
  }
  FordBellman(graph, answer, ver_num);
  for (auto& item : answer) {
    std::cout << item << ' ';
  }
  return 0;
}