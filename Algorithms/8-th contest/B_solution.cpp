#include <iostream>
#include <set>
#include <stack>
#include <vector>

struct request {
  std::string request;
  int first_vertex;
  int second_vertex;
};

class DisjointSet {
 public:
  DisjointSet(int n) {
    for (int i = 0; i < n; i++) {
      root_indices_.push_back(i);
    }
  }

  int find(int x) {
    if (root_indices_[x] == x) {
      return x;
    }
    return root_indices_[x] = find(root_indices_[x]);
  }

  void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
      root_indices_[y] = x;
    }
  }

  bool are_same(int x, int y) { return find(x) == find(y); }

 private:
  std::vector<int> root_indices_;
};

bool IsAsk(std::string& input) { return input == "ask"; }

int main() {
  int vertex_count = 0;
  int edges_count = 0;
  int req_num = 0;
  std::cin >> vertex_count >> edges_count >> req_num;

  for (int i = 0; i < edges_count; i++) {
    int u, v;
    std::cin >> u >> v;
  }

  std::stack<request> req;

  for (int i = 0; i < req_num; i++) {
    std::string request;
    int first_vertex;
    int second_vertex;
    std::cin >> request >> first_vertex >> second_vertex;
    req.push({request, first_vertex - 1, second_vertex - 1});
  }

  DisjointSet dsu(vertex_count);
  std::stack<std::string> answer;
  for (int i = 0; i < req_num; i++) {
    request new_req = req.top();
    req.pop();
    if (IsAsk(new_req.request)) {
      if (dsu.are_same(new_req.first_vertex, new_req.second_vertex)) {
        answer.emplace("YES\n");
      } else {
        answer.emplace("NO\n");
      }
    } else {
      dsu.unite(new_req.first_vertex, new_req.second_vertex);
    }
  }

  while (!answer.empty()) {
    std::cout << answer.top();
    answer.pop();
  }
  return 0;
}