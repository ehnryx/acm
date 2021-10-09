#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Graph {
  struct Edge {
    int other;
    int cost;
    Edge(int v, int c=0) {
      other = v;
      cost = c;
    }
  };
  int vertices;
  vector<vector<Edge>> g;
  Graph(int n) {
    vertices = n;
    g.resize(n);
  }
  void add_edge(int a, int b, int c=0) {
    g[a].push_back(Edge(b,c));
    if (c)
      g[b].push_back(Edge(a,c));
  }
  ll solve(int s, int t) {
    struct Node {
      int id;
      ll cost;
      bool fly;
      Node(int id=0, ll cost=0, bool f=true) {
        this->id = id;
        this->cost = cost;
        fly = f;
      }
      bool operator < (const Node& other) const {
        return other.cost < cost;
      }
    };
    ll dist[vertices][2]; // flyable
    memset(dist, INFLL, sizeof(dist));
    priority_queue<Node> next;
    next.push(Node(s, 0, true));
    Node cur;
    while (!next.empty()) {
      cur = next.top();
      next.pop();
      if (dist[cur.id][cur.fly] == INFLL) {
        dist[cur.id][cur.fly] = cur.cost;
        for (Edge e : g[cur.id]) {
          if (e.cost == 0) {
            if (cur.fly && dist[e.other][false] == INFLL) 
              next.push(Node(e.other, cur.cost, false));
          } else {
            if (dist[e.other][cur.fly] == INFLL)
              next.push(Node(e.other, e.cost + cur.cost, cur.fly));
          }
        }
      }
    }
    return min(dist[t][true], dist[t][false]);
  }
};

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int a, b, c;
  int n, m, f, s, t;
  cin >> n >> m >> f >> s >> t;
  Graph graph(n);
  for (int i = 0; i < m; i++) {
    cin >> a >> b >> c;
    graph.add_edge(a,b,c);
  }
  for (int i = 0; i < f; i++) {
    cin >> a >> b;
    graph.add_edge(a,b,0);
  }
  cout << graph.solve(s,t) << endl;

  return 0;
}
