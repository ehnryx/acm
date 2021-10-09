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

const int N = 17;

int root[N];
int adj[N][N];

int find(int i) {
  if (root[i] == -1) return i;
  return root[i] = find(root[i]);
}

int link(int i, int j) {
  if (find(i) == find(j)) return 0;
  root[find(i)] = find(j);
  return 1;
}

void init() {
  memset(adj, INF, sizeof adj);
}

struct Edge {
  int a, b, c;
  Edge() {}
  Edge(int a, int b, int c): a(a), b(b), c(c) {}
  bool operator < (const Edge& e) const {
    return c < e.c;
  }
};

int mst(int bm) {
  memset(root, -1, sizeof root);
  vector<Edge> edges;
  for (int i = 1; i < N; i++) {
    for (int j = 1; j < i; j++) {
      if ((bm & 1<<i) && (bm & 1<<j) && adj[i][j] < INF) {
        edges.push_back(Edge(i, j, adj[i][j]));
      }
    }
  }
  sort(edges.begin(), edges.end());

  int n = __builtin_popcount(bm);
  int res = 0;
  for (const Edge& e : edges) {
    if (link(e.a, e.b)) {
      n--;
      res += e.c;
    }
  }

  if (n == 1) return res;
  else return INF;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while (T--) {
    init();
    int n, m, k;
    cin >> n >> m >> k;

    int a, b, c;
    for (int i = 0; i < m; i++) {
      cin >> a >> b >> c;
      adj[a][b] = c;
      adj[b][a] = c;
    }

    int special = 0;
    for (int i = 0; i < k; i++) {
      cin >> a;
      special |= 1<<a;
    }

    int ans = INF;
    for (int bm = 0; bm < 1<<n; bm++) {
      if ((bm<<1 & special) == special) {
        ans = min(ans, mst(bm<<1));
      }
    }
    cout << ans << nl;
  }

  return 0;
}
