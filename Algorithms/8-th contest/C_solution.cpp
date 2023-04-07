// 84384679
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

namespace graph {
template <typename T, typename U = size_t>
struct DefaultEdge : std::pair<std::pair<T, T>, U> {
  DefaultEdge(const T& first, const T& second, const U& weight)
      : std::pair<std::pair<T, T>, U>(std::pair(first, second), weight) {}
  using BaseClass = std::pair<std::pair<T, T>, U>;
  const T& Start() const { return BaseClass::first.first; }
  const T& Finish() const { return BaseClass::first.second; }
  const T& Weight() const { return BaseClass::second; }
};

template <typename Vertex = int64_t, typename Weight = int64_t,
          typename Edge = DefaultEdge<Vertex, Weight>>
class AbstractGraph {
 public:
  using VertexType = Vertex;
  using EdgeType = Edge;
  using WeightType = Weight;

  explicit AbstractGraph(int64_t vertices_num, int64_t edges_num = 0)
      : vertices_number_(vertices_num), edges_number_(edges_num) {}
  int64_t GetVerticesNumber() const { return vertices_number_; }
  int64_t GetEdgesNumber() const { return edges_number_; }
  virtual std::vector<std::pair<Vertex, Weight>> GetNeighbours(
      const Vertex& vertex) = 0;

 protected:
  int64_t vertices_number_ = 0;

  int64_t edges_number_ = 0;
};
}  // namespace graph

namespace graph {
template <typename Vertex = int64_t, typename Weight = int64_t,
          typename Edge = DefaultEdge<Vertex, Weight>>
class AdjacencyListGraph : public AbstractGraph<Vertex, Weight, Edge> {
 public:
  AdjacencyListGraph(Vertex vertices_num, std::vector<Edge>& edges)
      : AbstractGraph<Vertex, Weight, Edge>(vertices_num, edges.size()) {
    for (const auto& edge : edges) {
      list_[edge.Start()].push_back({edge.Finish(), edge.Weight()});
      list_[edge.Finish()].push_back({edge.Start(), edge.Weight()});
    }
  }
  std::vector<std::pair<Vertex, Weight>> GetNeighbours(
      const Vertex& vertex) final {
    return list_[vertex];
  }

 private:
  std::unordered_map<Vertex, std::vector<std::pair<Vertex, Weight>>> list_;
};
}  // namespace graph

namespace maps::visitors {
template <class Vertex, class Edge, class Weight>
class DijkstraVisitor {
 public:
  virtual void Ancestor(const Edge&) = 0;
  virtual void DistUpdate(const Weight&, const Vertex&) = 0;
  virtual ~DijkstraVisitor() = default;
};

}  // namespace maps::visitors

namespace maps::visitors {
template <class Vertex, class Edge, class Weight>
class AncestorDijkstraVisitor : DijkstraVisitor<Vertex, Edge, Weight> {
 public:
  explicit AncestorDijkstraVisitor(const int64_t& size) : dist_(size, kInf){};
  void Ancestor(const Edge& edge) override {
    ancestors_[edge.Finish()] = edge.Start();
  }

  void DistUpdate(const Weight& weight, const Vertex& vertex) override {
    dist_[vertex] = weight;
  }

  std::vector<Vertex> GetDist() const { return dist_; }

  Weight GetCurrDist(const Vertex& vertex) const { return dist_[vertex]; }

  std::unordered_map<Vertex, Vertex> GetMap() const { return ancestors_; }

 private:
  const Weight kInf = 2009000999;

  std::unordered_map<Vertex, Vertex> ancestors_;

  std::vector<Weight> dist_;
};

}  // namespace maps::visitors

namespace maps {

template <typename Weight, class Vertex, class Graph, class Visitor>
void Dijkstra(Vertex origin, Graph& graph, Visitor& visitor) {
  std::set<std::pair<Weight, Vertex>> set_min;
  visitor.DistUpdate(0, origin);
  set_min.insert({0, origin});
  while (!set_min.empty()) {
    Vertex into = set_min.begin()->second;
    set_min.erase(set_min.begin());
    auto vector = graph.GetNeighbours(into);
    for (auto& edge : vector) {
      Vertex from = edge.first;
      Weight weight = edge.second;

      if (visitor.GetCurrDist(into) + weight < visitor.GetCurrDist(from)) {
        set_min.erase({visitor.GetCurrDist(from), from});
        visitor.DistUpdate(visitor.GetCurrDist(into) + weight, from);
        set_min.insert({visitor.GetCurrDist(from), from});
      }
    }
  }
}

}  // namespace maps

namespace dsu {
template <class Vertex = size_t>
class DSU {
 public:
  DSU(size_t size) {
    parent_ = std::vector<Vertex>(size);
    rank_ = std::vector<Vertex>(size);
    for (size_t i = 0; i < size; i++) {
      parent_[i] = Vertex(i);
      rank_[i] = 0;
    }
    set_num_ = size;
  }
  void Unite(Vertex first, Vertex second) {
    auto first_got = Find(first);
    auto second_got = Find(second);
    if (first_got == second_got) {
      return;
    }
    if (rank_[first_got] == rank_[second_got]) {
      rank_[first_got]++;
    }
    if (rank_[first_got] < rank_[second_got]) {
      parent_[first_got] = second_got;
    } else {
      parent_[second_got] = first_got;
    }
    set_num_--;
  }
  bool AreSame(Vertex first, Vertex second) {
    return Find(first) == Find(second);
  }

 private:
  size_t Find(Vertex elem) {
    if (parent_[elem] != elem) {
      parent_[elem] = Find(parent_[elem]);
    }
    return parent_[elem];
  }

  std::vector<Vertex> parent_;

  size_t set_num_;

  std::vector<size_t> rank_;
};
}  // namespace dsu

namespace graph {
template <typename Vertex = size_t, typename Weight = size_t,
          typename Edge = DefaultEdge<Vertex, Weight>>
class MST : public AbstractGraph<Vertex, Weight, Edge> {
 public:
  MST(Vertex vertices_num, std::vector<Edge>& edges)
      : AbstractGraph<Vertex, Weight, Edge>(vertices_num, edges.size()) {
    edge_tree_ = edges;
  }
  // NOLINTNEXTLINE
  typename std::vector<Edge>::iterator begin() { return edge_tree_.begin(); }
  // NOLINTNEXTLINE
  typename std::vector<Edge>::iterator end() { return edge_tree_.end(); }

  std::vector<std::pair<Vertex, Weight>> GetNeighbours(
      const Vertex& vertex) override {
    std::vector<std::pair<Vertex, Weight>> ret_type;
    for (const auto& edge : edge_tree_) {
      if (edge.Start() == vertex || edge.Finish() == vertex) {
        std::pair<Vertex, Weight> ret_pair = {edge.Start(), edge.Weight()};
        ret_type.push_back(ret_pair);
      }
    }
    return ret_type;
  }

  Weight total_weight = 0;

 private:
  std::vector<Edge> edge_tree_;
};
}  // namespace graph

namespace mst {
template <typename Weight, class Vertex,
          class Edge = graph::DefaultEdge<Vertex, Weight>>
bool Compare(Edge& first, Edge& second) {
  return first.Weight() < second.Weight();
}

template <typename Weight, class Vertex, class Graph>
graph::MST<Vertex, Weight> Kruskal(Graph& graph) {
  std::sort(graph.begin(), graph.end(), Compare<Weight, Vertex>);
  dsu::DSU<Vertex> dsu(graph.GetVerticesNumber());
  std::vector<graph::DefaultEdge<size_t>> edges;
  Weight total_weight = 0;
  for (const auto& edge : graph) {
    Vertex first_vertex = edge.Start();
    Vertex second_vertex = edge.Finish();
    Weight weight = edge.Weight();

    if (!dsu.AreSame(first_vertex, second_vertex)) {
      total_weight += weight;
      dsu.Unite(first_vertex, second_vertex);
      graph::DefaultEdge<Vertex> edge_to(first_vertex, second_vertex, weight);
      edges.push_back(edge_to);
    }
  }
  graph::MST<Vertex, Weight> answer(graph.GetVerticesNumber(), edges);
  answer.total_weight = total_weight;
  return answer;
}

template <typename Weight, class Vertex, class Graph>
graph::MST<Vertex, Weight> Prim(Graph& graph, Vertex start_vertex) {
  using Edge = graph::DefaultEdge<Weight>;
  using EdgesHeap = std::priority_queue<Edge, std::vector<Edge>>;

  EdgesHeap edges_heap;
  std::vector<bool> used(graph.GetVerticesNumber(), false);
  std::vector<Edge> edges;

  used[start_vertex] = true;
  for (const auto& edge : graph.GetAdjacentEdges(start_vertex)) {
    edges_heap.push(edge);
  }

  while (!edges_heap.empty()) {
    Edge min_edge = edges_heap.top();
    edges_heap.pop();

    Vertex first_vertex = min_edge.Start();
    Vertex second_vertex = min_edge.Finish();

    if (used[first_vertex] && used[second_vertex]) {
      continue;
    }

    edges.push_back(min_edge);

    Vertex new_vertex = used[first_vertex] ? second_vertex : first_vertex;
    used[new_vertex] = true;

    for (const auto& edge : graph.GetAdjacentEdges(new_vertex)) {
      if (!used[edge.Finish()]) {
        edges_heap.push(edge);
      }
    }
  }
  graph::MST<Vertex, Weight> answer(graph.GetVerticesNumber(), edges);
  Weight total_weight = 0;
  for (const auto& edge : edges) {
    total_weight += edge.Weight();
  }
  answer.total_weight = total_weight;
  return answer;
}

}  // namespace mst

int main() {
  size_t vertex_count = 0;
  size_t edge_count = 0;
  std::cin >> vertex_count >> edge_count;
  std::vector<graph::DefaultEdge<size_t>> edges;
  for (size_t i = 0; i < edge_count; i++) {
    size_t first_vertex = 0;
    size_t second_vertex = 0;
    size_t weight = 0;
    std::cin >> first_vertex >> second_vertex >> weight;
    graph::DefaultEdge<size_t> edge(first_vertex - 1, second_vertex - 1,
                                    weight);
    edges.push_back(edge);
  }
  graph::MST<size_t, size_t> graph(vertex_count, edges);
  graph = mst::Kruskal<size_t, size_t>(graph);
  std::cout << graph.total_weight << '\n';
  return 0;
}