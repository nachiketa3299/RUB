#include <iostream>
#include <vector>
#include <algorithm>

// 09:05

using namespace std;

struct Edge {
  int head, tail;
  int weight;
  bool operator<(const Edge& oth) const { 
    return weight < oth.weight; 
  }
  friend istream& operator>>(istream& in, Edge& oth) {
    in >> oth.head >> oth.tail >> oth.weight;
    return in;
  }
};

struct UnionFind {
  UnionFind(int vcount): parent(vcount + 1) {
    for (int i = 1; i < parent.size(); ++i) {
      parent[i] = i;
    }
  };

  int Find(int x) {
    if (parent[x] == x) {
      return x;
    }

    return parent[x] = Find(parent[x]);
  }

  bool Unite(int n1, int n2) {
    int p1 = Find(n1);
    int p2 = Find(n2);

    if (p1 == p2) {
      return false;
    }

    parent[p2] = p1;
    return true;
  }

  vector<int> parent;
};

int main() {

  int N, M; // N [2, 10^5 M 1, 10^6]
  cin >> N >> M;

  vector<Edge> edges(M);
  for (Edge& edge: edges) {
    cin >> edge;
  }

  sort(edges.begin(), edges.end());
  UnionFind uf{N};

  int total_w{}, max_w{};

  for (size_t i = 0; i < edges.size(); ++i) {
    const auto& [h, t, w] = edges[i];

    if (uf.Unite(h, t)) {
      total_w += w;
      max_w = w;
    }
  }

  cout << total_w - max_w;
}