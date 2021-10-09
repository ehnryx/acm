#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

struct Graph {
  struct Edge {
    int other;
    int left, right;
    Edge(int o, int l, int r): other(o), left(l), right(r) {}
  };
  int vertices;
  vector<int> points;
  vector<vector<Edge>> g;
  Graph(int n) {
    vertices = n;
    g.resize(n);
  }
  void add_edge(int a, int b, int c, int d) {
    g[a].push_back(Edge(b, c, d));
  }
  void add_point(int v) {
    points.push_back(v);
  }
  bool dfs(int s, int t, int v) {
    vector<bool> vis(vertices);
    stack<int> next;
    next.push(s);
    vis[s] = true;
    while (!next.empty()) {
      int cur = next.top();
      next.pop();
      if (cur == t) 
        return true;
      for (const Edge& e : g[cur]) {
        if (!vis[e.other] && e.left <= v && v <= e.right) {
          next.push(e.other);
          vis[e.other] = true;
        }
      }
    }
    return false;
  }
  int count(int s, int t) {
    sort(points.begin(), points.end());
    int prev = -1;
    int ans = 0;
    for (int p : points) {
      if (dfs(s, t, p)) {
        if (prev == -1)
          prev = p;
      } else {
        if (prev > 0)
          ans += p - prev;
        prev = -1;
      }
    }
    return ans;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int a, b, c, d;
  int n, m, k;
  int s, t;
  cin >> n >> m >> k;
  cin >> s >> t;
  Graph graph(n+1);
  graph.add_point(1);
  graph.add_point(k+1);
  for (int i = 0; i < m; i++) {
    cin >> a >> b >> c >> d;
    graph.add_edge(a,b,c,d);
    graph.add_point(c);
    graph.add_point(d+1);
  }
  cout << graph.count(s, t) << nl;

  return 0;
}
