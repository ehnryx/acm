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
  int n;
  int vertices;
  vector<vector<int>> g, r;
  Graph(int n): n(n) {
    vertices = 2*n+2;
    g.resize(vertices);
    r.resize(vertices);
  }
  void add_edge(int a, int b) {
    g[a].push_back(b);
    r[b].push_back(a);
  }
  
  bool search(int s, int t) {
    vector<bool> vis(vertices);
    stack<int> next;
    next.push(s);
    vis[s] = true;
    while (!next.empty()) {
      int cur = next.top();
      next.pop();
      if (cur == t) 
        return true;
      for (int neighbour : g[cur]) {
        if (!vis[neighbour]) {
          next.push(neighbour);
          vis[neighbour] = true;
        }
      }
    }
    return false;
  }

  bool find(int s, bool state) {
    vector<bool> vis(vertices);
    stack<int> next;
    next.push(s);
    vis[s] = true;
    while (!next.empty()) {
      int cur = next.top();
      next.pop();
      if (!state && cur < n)
        return true;
      if (state && cur > n)
        return true;
      for (int neighbour : g[cur]) {
        if (!vis[neighbour]) {
          next.push(neighbour);
          vis[neighbour] = true;
        }
      }
    }
    return false;
  }

  bool reverse(int s, bool state) {
    vector<bool> vis(vertices);
    stack<int> next;
    next.push(s);
    vis[s] = true;
    while (!next.empty()) {
      int cur = next.top();
      next.pop();
      if (!state && cur < n)
        return true;
      if (state && cur > n)
        return true;
      for (int neighbour : r[cur]) {
        if (!vis[neighbour]) {
          next.push(neighbour);
          vis[neighbour] = true;
        }
      }
    }
    return false;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int a, b;
  int n, m;
  cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; i++) {
    cin >> a >> b;
    graph.add_edge(n-a, n+b);
    graph.add_edge(n-b, n+a);
  }
  int ans = INF;
  int temp, possible;
  for (int i = 1; i <= n; i++) {
    temp = 0;
    if (!graph.search(n+i, n-i)) {
      possible = (graph.find(n+i, false) && graph.reverse(n-i, true));
      if (!possible) continue;
      else temp += possible;
    }
    if (!graph.search(n-i, n+i)) {
      possible = (graph.find(n-i, false) && graph.reverse(n+1, true));
      if (!possible) continue;
      else temp += possible;
    }
    ans = min(ans, temp);
  }
  if (ans == INF) 
    ans = -1;
  cout << ans << nl;

  return 0;
}
