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
  int vertices;
  vector<vector<pair<int,int>>> g;
  vector<int> cnt;
  Graph(int n) {
    g.resize(n);
    cnt.resize(n);
    vertices = n;
  }
  void add_stuff(int a, int v) {
    cnt[a] = v;
  }
  void add_edge(int a, int b, int c) {
    g[a].push_back(pii(b,c));
    g[b].push_back(pii(a,c));
  }
  pair<int,int> dijkstra(int s, int t) {
    struct Node {
      int id;
      int dist;
      int stuff;
      Node(int id=-1, int dist=INF, int stuff=0) {
        this->id = id;
        this->dist = dist;
        this->stuff = stuff;
      }
      bool operator < (const Node& other) const {
        if (dist == other.dist) return other.stuff > stuff;
        else return other.dist < dist;
      }
    };
    int dist[vertices];
    memset(dist, INF, sizeof(dist));

    Node curr;
    priority_queue<Node> next;
    next.push(Node(s, 0, cnt[s]));
    while (!next.empty()) {
      curr = next.top();
      next.pop();
      if (curr.id == t) {
        return pair<int,int>(curr.dist, curr.stuff);
      }
      if (dist[curr.id] == INF) {
        dist[curr.id] == INF;
        dist[curr.id] = curr.dist;
        for (pii neighbour : g[curr.id]) {
          if (dist[neighbour.first] == INF)
            next.push(Node(
                  neighbour.first, 
                  curr.dist + neighbour.second,
                  curr.stuff + cnt[neighbour.first]));
        }
      }
    }
    return pii(-1,-1);
  }
};

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int n, a, b, c;
  cin >> n;
  Graph graph(n);
  for (int i = 0; i < n; i++) {
    cin >> c;
    graph.add_stuff(i,c);
  }
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a >> b >> c;
    graph.add_edge(a-1,b-1,c);
  }
  pair<int,int> ans = graph.dijkstra(0, graph.vertices-1);
  if (ans.first == -1) cout << "impossible" << endl;
  else cout << ans.first << " " << ans.second << endl;

  return 0;
}
