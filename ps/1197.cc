#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct UnionFind {

  UnionFind(int ncount): parent(ncount + 1) {
    for (size_t i = 1; i < parent.size(); ++i) {
      parent[i] = i;
    }
  }

  int Find(int vidx) {
    if (parent[vidx] == vidx) {
      return vidx;
    }

    return parent[vidx] = Find(parent[vidx]);
  }

  void Unite(int n1idx, int n2idx) {
    int n1p{Find(n1idx)}, n2p{Find(n2idx)};

    if (n1p != n2p) {
      parent[n2p] = n1p;
    }
  }

private:
  vector<int> parent;
};

int main() {
  int V, E; cin >> V >> E;
  // V 10^4 E 10^5
  UnionFind uf{V};

  struct Edge {
    size_t head, tail;
    int weight;
    bool operator<(const Edge& oth) const {
      return weight < oth.weight;
    }
  };

  vector<Edge> edges(E);
  for (Edge& edge: edges) {
    cin >> edge.head >> edge.tail >> edge.weight;
  }

  sort(edges.begin(), edges.end());
  long long total_weight{};

  for (const auto& [h, t, w]: edges) {
    if (uf.Find(h) != uf.Find(t)) {
      uf.Unite(h, t);

      total_weight += w;
    }
  }

  cout << total_weight << '\n';
}
