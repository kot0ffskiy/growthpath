#include <iostream>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

namespace graph {
template <typename T, typename U = int64_t>
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

int main() {
  int64_t map_num = 0;
  std::cin >> map_num;
  for (int64_t i = 0; i < map_num; ++i) {
    int64_t num_ver = 0;
    int64_t num_edg = 0;
    std::cin >> num_ver >> num_edg;
    std::vector<graph::DefaultEdge<int64_t>> edges;
    for (int64_t l = 0; l < num_edg; ++l) {
      int64_t from = 0;
      int64_t into = 0;
      int64_t weight = 0;
      std::cin >> from >> into >> weight;
      graph::DefaultEdge<int64_t> edge(from, into, weight);
      edges.push_back(edge);
    }
    graph::AdjacencyListGraph<int64_t, int64_t, graph::DefaultEdge<int64_t>>
        graph(num_ver, edges);
    maps::visitors::AncestorDijkstraVisitor<
        int64_t, graph::DefaultEdge<int64_t>, int64_t>
        visitor(num_ver);
    int64_t start = 0;
    std::cin >> start;

    maps::Dijkstra<int64_t>(start, graph, visitor);
    auto result = visitor.GetDist();
    for (auto& item : result) {
      std::cout << item << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}