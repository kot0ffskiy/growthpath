#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

const int64_t kInf = 1e13;

void Dijkstra(int64_t treatment,
              std::vector<std::vector<std::pair<int64_t, int64_t>>>& adj_list,
              std::set<std::pair<int64_t, int64_t>>& set_min,
              std::vector<int64_t>& dist) {
  dist[treatment] = 0;
  set_min.insert({0, treatment});

  while (!set_min.empty()) {
    int64_t into = set_min.begin()->second;
    set_min.erase(set_min.begin());

    for (auto& edge : adj_list[into]) {
      int64_t from = edge.first;
      int64_t weight = edge.second;

      if (dist[into] + weight < dist[from]) {
        set_min.erase({dist[from], from});
        dist[from] = dist[into] + weight;
        set_min.insert({dist[from], from});
      }
    }
  }
}

void PrintDistance(int64_t start, std::vector<int64_t>& infected,
                   std::vector<int64_t>& dist) {
  if (dist[start] == kInf) {
    std::cout << "-1\n";
    return;
  }
  for (auto& ver : infected) {
    if (dist[ver] <= dist[start]) {
      std::cout << "-1\n";
      return;
    }
  }
  std::cout << dist[start] << "\n";
}

int main() {
  int64_t num_ver = 0;
  int64_t num_edges = 0;
  int64_t num_viruses = 0;
  std::cin >> num_ver >> num_edges >> num_viruses;

  std::vector<int64_t> infected(num_viruses);
  for (int64_t i = 0; i < num_viruses; i++) {
    std::cin >> infected[i];
  }

  std::vector<std::vector<std::pair<int64_t, int64_t>>> adj_list(num_ver + 1);
  for (int64_t i = 0; i < num_edges; i++) {
    int64_t from = 0;
    int64_t into = 0;
    int64_t weight = 0;
    std::cin >> from >> into >> weight;
    adj_list[from].emplace_back(into, weight);
    adj_list[into].emplace_back(from, weight);
  }

  int64_t start = 0;
  int64_t treatment = 0;
  std::cin >> start >> treatment;

  std::set<std::pair<int64_t, int64_t>> set_min;

  std::vector<int64_t> dist(num_ver + 1, kInf);

  Dijkstra(treatment, adj_list, set_min, dist);
  PrintDistance(start, infected, dist);

  return 0;
}