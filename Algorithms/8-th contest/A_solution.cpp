#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

template <typename Vertex, typename Weight = size_t>
class DisjointSet {
 public:
  DisjointSet(size_t size);
  void Unite(Vertex first, Vertex second, Weight weight);
  [[nodiscard]] Weight GetWeight(Vertex vertex) const;
  Vertex Find(Vertex elem);

 private:
  std::unordered_map<Vertex, Vertex> ancestors_;
  std::unordered_map<Vertex, size_t> tree_size_;
  std::unordered_map<Vertex, Weight> weight_;
};

template <typename Vertex, typename Weight>
Vertex DisjointSet<Vertex, Weight>::Find(Vertex elem) {
  auto found = ancestors_.find(elem);
  if (found->second == elem) {
    return found->second;
  }
  return found->second = Find(found->second);
}

template <typename Vertex, typename Weight>
Weight DisjointSet<Vertex, Weight>::GetWeight(Vertex vertex) const {
  auto found = weight_.find(vertex);
  return found == weight_.end() ? 0 : found->second;
}

template <typename Vertex, typename Weight>
void DisjointSet<Vertex, Weight>::Unite(Vertex first, Vertex second,
                                        Weight weight) {
  auto first_found = Find(first);
  auto second_found = Find(second);
  if (first_found == second_found) {
    weight_[first_found] = weight + weight_[second_found];
    return;
  }
  if (tree_size_[first_found] < tree_size_[second_found]) {
    std::swap(first_found, second_found);
  }
  ancestors_[second_found] = first_found;
  weight_[second_found] = weight + weight_[second_found];
  weight_[first_found] += weight_[second_found];

  if (tree_size_[first_found] == tree_size_[second_found]) {
    tree_size_[first_found]++;
  }
}

template <typename Vertex, typename Weight>
DisjointSet<Vertex, Weight>::DisjointSet(size_t size) {
  for (int i = 0; i < size; i++) {
    auto elem = Vertex(i);
    ancestors_[elem] = elem;
    tree_size_[elem] = 1;
  }
}

template <typename Weight>
class DisjointSet<size_t, Weight> {
 public:
  DisjointSet(size_t size);
  void Unite(size_t first, size_t second, Weight weight);
  [[nodiscard]] Weight GetWeight(size_t vertex);

 private:
  std::vector<size_t> ancestors_;
  std::vector<size_t> tree_size_;
  std::vector<Weight> weight_;
  size_t Find(size_t elem);
};

template <typename Weight>
size_t DisjointSet<size_t, Weight>::Find(size_t elem) {
  if (ancestors_[elem] != elem) {
    ancestors_[elem] = Find(ancestors_[elem]);
  }
  return ancestors_[elem];
}

template <typename Weight>
Weight DisjointSet<size_t, Weight>::GetWeight(size_t vertex) {
  return weight_[Find(vertex)];
}

template <typename Weight>
void DisjointSet<size_t, Weight>::Unite(size_t first, size_t second,
                                        Weight weight) {
  auto first_found = Find(first);
  auto second_found = Find(second);
  if (tree_size_[first_found] == tree_size_[second_found]) {
    tree_size_[first_found]++;
  }
  if (first_found == second_found) {
    weight_[first_found] = weight + weight_[second_found];
    return;
  }
  if (tree_size_[first_found] < tree_size_[second_found]) {
    std::swap(first_found, second_found);
  }
  ancestors_[second_found] = first_found;
  weight_[second_found] = weight + weight_[second_found];
  weight_[first_found] += weight_[second_found];
}

template <typename Weight>
DisjointSet<size_t, Weight>::DisjointSet(size_t size)
    : ancestors_(std::vector<size_t>(size)),
      weight_(std::vector<Weight>(size)),
      tree_size_(std::vector<size_t>(size, 1)) {
  for (int i = 0; i < size; i++) {
    auto elem = i;
    ancestors_[elem] = elem;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t vertex_count = 0;
  size_t query_count = 0;
  std::cin >> vertex_count >> query_count;

  DisjointSet<size_t, size_t> dsu(vertex_count);

  for (size_t i = 0; i < query_count; i++) {
    size_t query = 0;
    std::cin >> query;
    // add
    if (query == 1) {
      size_t first_vertex = 0;
      size_t second_vertex = 0;
      size_t weight = 0;
      std::cin >> first_vertex >> second_vertex >> weight;
      dsu.Unite(first_vertex - 1, second_vertex - 1, weight);
    } else if (query == 2) {
      size_t tofind = 0;
      std::cin >> tofind;
      std::cout << dsu.GetWeight(tofind - 1) << '\n';
    }
  }
  return 0;
}