#include <bits/stdc++.h>
using namespace std;

int INF = 0x3f3f3f3f;

struct Graph {
  struct Edge {
    int other;
    int cost;
    Edge(int v, int c) {
      other = v;
      cost = c;
    }
  };

  int vertices;
  vector<vector<Edge>> g;
  Graph(int v) {
    vertices = v;
    g.resize(v);
  }
  void add_edge(int a, int b, int c) {
    g[a].push_back(Edge(b,c));
  }

  int dijkstra(int s, int t) {

    struct Item {
      int id;
      int dist;
      Item(int id=-1, int dist=INF) {
        this->id = id;
        this->dist = dist;
      }
      bool operator < (const Item& other) const {
        return other.dist < this->dist;
      }
    };

    int dist[vertices];
    memset(dist, INF, sizeof(dist));

    priority_queue<Item> next;
    next.push(Item(s,0));

    Item cur;
    while (!next.empty()) {
      cur = next.top();
      next.pop();
      if (cur.id == t) {
        return cur.dist;
      }
      if (dist[cur.id] == INF) {
        dist[cur.id] = cur.dist;
        for (Edge e : g[cur.id]) {
          if (dist[e.other] == INF) {
            next.push(Item(e.other, cur.dist + e.cost));
          }
        }
      }
    }
    return -1;
  }
};

int main() {
  ios::sync_with_stdio(0);

  int a, b, c;
  int v, e;
  cin >> v >> e;
  Graph graph(v);
  for (int i = 0 ; i < e; i++) {
    cin >> a >> b >> c;
    graph.add_edge(a,b,c);
  }
  cout << graph.dijkstra(0, 4) << '\n';

  return 0;
}
