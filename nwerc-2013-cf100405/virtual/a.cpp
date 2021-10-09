#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Edge {
  int a, b, c;
  Edge(): a(0), b(0), c(1e6+1) {}
  Edge(int a, int b, int c): a(a), b(b), c(c) {}
  bool operator < (const Edge& v) const {
    return c < v.c;
  }
};

const int N = 2001;
int dist[N][N];
bool vis[N];
int d2[N][N];
vector<pii> adj[N];
int root[N];

void init() {
  iota(root, root + N, 0);
  memset(d2, INF, sizeof d2);
  fill(adj, adj+N, vector<pii>());
}

int find(int i) {
  if (root[i] == i) return i;
  return root[i] = find(root[i]);
}

void link(int i, int j) {
  root[find(i)] = find(j);
}

void dfs(int cur, int root, int par) {
  for (const auto& p : adj[cur]) {
    int i = p.first, c = p.second;
    if (i != par) {
      d2[root][i] = d2[root][cur] + c;
      dfs(i, root, cur);
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  while (cin >> n) {
    init();

    vector<Edge> edges;
    for (int i=1; i<=n; i++) {
      for (int j=1; j<=n; j++) {
        cin >> dist[i][j];
        if (i < j) {
          edges.push_back(Edge(i,j,dist[i][j]));
        }
      }
    }
    sort(edges.begin(), edges.end());

    vector<Edge> e_bad;
    for (const Edge& e : edges) {
      if (find(e.a) == find(e.b)) {
        e_bad.push_back(e);
      } else {
        link(e.a, e.b);
        cout << e.a << " " << e.b << " " << e.c << nl;
        adj[e.a].push_back({e.b, e.c});
        adj[e.b].push_back({e.a, e.c});
      }
    }

    for (int i = 1; i <= n; i++) {
      d2[i][i] = 0;
      dfs(i, i, -1);
    }

    Edge add;
    for (const Edge& e : e_bad) {
      if (e.c != d2[e.a][e.b]) {
        add = min(add, e);
      }
    }

    if (add.a == 0) {
      cout << 1 << " " << 2 << " " << dist[1][2] << nl;
    } else {
      cout << add.a << " " << add.b << " " << add.c << nl;
    }

    cout << nl;
  }

  return 0;
}
