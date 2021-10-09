#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ ";
  for (const T& it : v) os << it << " ";
  os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ ";
  for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
  os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

set<pii> good;

void dfs(int s, const vector<vector<int>>& g, int dir) {
  vector<bool> vis(g.size());
  stack<int> next;
  next.push(s);
  vis[s] = true;
  while (!next.empty()) {
    s = next.top();
    next.pop();
    for (int x : g[s]) {
      if (!vis[x]) {
        if (dir)
          good.insert(pii(s, x));
        else 
          good.insert(pii(x, s));
        next.push(x);
        vis[x] = true;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int T;
  cin >> T;
  while (T--) {
    good.clear();

    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n+1);
    vector<vector<int>> rev(n+1);

    int a, b;
    vector<pii> edges;
    for (int i = 0; i < m; i++) {
      cin >> a >> b;
      graph[a].push_back(b);
      rev[b].push_back(a);
      edges.push_back(pii(a,b));
    }

    dfs(1, graph, 1);
    dfs(1, rev, 0);
    for (int i = 0; good.size() < 2*n; i++) {
      good.insert(edges[i]);
    }
    for (int i = 0; i < m; i++) {
      if (!good.count(edges[i])) {
        cout << edges[i].first << " " << edges[i].second << nl;
      }
    }
  }

  return 0;
}
