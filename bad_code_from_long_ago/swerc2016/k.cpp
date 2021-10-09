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

struct Point {
  int x, y, z;
  Point(int x=0, int y=0, int z=0):
    x(x), y(y), z(z) {}
  bool operator < (const Point& other) const {
    if (x != other.x) return x < other.x;
    if (y != other.y) return y < other.y;
    return z < other.z;
  }
};

struct Graph {
  vector<set<int>> g;
  vector<set<int>> s;
  void add_edge(int a, int b) {
    g[a].insert(b);
    g[b].insert(a);
  }
  void add_shadow(int a, int b) {
    s[a].insert(b);
    s[b].insert(a);
  }
  bool cycle() {
    vector<int> par(g.size());
    vector<bool> vis(g.size());
    stack<int> next;
    for (int i = 0; i < g.size(); i++) {
      if (vis[i]) continue;
      next.push(i);
      vis[i] = true;
      par[i] = -1;
      while (!next.empty()) {
        int cur = next.top();
        next.pop();
        //cerr << "visit " << cur << nl;
        for (int u : g[cur]) {
          //cerr << "cur: " << cur << "  u: " << u << nl;
          if (u == cur || u == par[cur])
            continue;
          if (vis[u]) {
            //cerr << u << " already visited" << nl;
            return true;
          }
          //cerr << "from " << cur << " push " << u << nl;
          next.push(u);
          vis[u] = true;
          par[u] = cur;
        }
      }
    }
    return false;
  }
  bool shadow() {
    vector<bool> vis(s.size());
    vector<int> par(s.size());
    stack<int> next;
    for (int i = 0; i < s.size(); i++) {
      if (vis[i]) continue;
      next.push(i);
      vis[i] = true;
      par[i] = -1;
      while (!next.empty()) {
        int cur = next.top();
        next.pop();
        for (int u : s[cur]) {
          if (u == cur || u == par[cur]) 
            continue;
          if (vis[u]) { 
            return true;
          }
          next.push(u);
          vis[u] = true;
          par[u] = cur;
        }
      }
    }
    return false;
  }
};

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  Graph graph;
  Point a, b;
  map<Point, int> m;
  map<Point, int> s;
  int n;
  cin >> n;
  int mcount = 0;
  int scount = 0;
  for (int i = 0; i < n; i++) {
    cin >> a.x >> a.y >> a.z >> b.x >> b.y >> b.z;
    if (!m.count(a)) {
      m[a] = mcount++;
      graph.g.push_back({});
    }
    if (!m.count(b)) {
      m[b] = mcount++;
      graph.g.push_back({});
    }
    //cerr << "add edge: " << m[a] << " " << m[b] << nl;
    graph.add_edge(m[a], m[b]);
    a.z = b.z = 0;
    if (!s.count(a)) {
      s[a] = scount++;
      graph.s.push_back({});
    }
    if (!s.count(b)) {
      s[b] = scount++;
      graph.s.push_back({});
    }
    //cerr << "add shadow: " << s[a] << " " << s[b] << nl;
    graph.add_shadow(s[a], s[b]);
  }

  //cerr; for (auto it : m) {
    //cerr << it.first.x << " " << it.first.y << " " << it.first.z << " : " << it.second << nl;}

  if (graph.cycle()) cout << "True closed chains" << nl;
  else cout << "No true closed chains" << nl;
  if (graph.shadow()) cout << "Floor closed chains" << nl;
  else cout << "No floor closed chains" << nl;

  return 0;
}
