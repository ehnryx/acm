#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Edge {
  int a, b, c;
  Edge(){}
  Edge(int a, int b, int c): a(a), b(b), c(c) {}
};

const int N = 2002;
ll dist[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while (T--) {
    int n, m;
    cin >> n >> m;

    int a, b, c;
    vector<Edge> edges;
    int mincost = INF;
    for (int i = 0; i < m; i++) {
      cin >> a >> b >> c;
      edges.push_back(Edge(a,b,c));
      mincost = min(mincost, c);
    }

    for (int i = 1; i <= n; i++) {
      edges.push_back(Edge(0,i,0));
      edges.push_back(Edge(i,n+1,0));
    }

    memset(dist, INF, sizeof dist);
    dist[0] = 0;
    for (int i = 1; i < n+2; i++) {
      for (const Edge& e : edges) {
        dist[e.b] = min(dist[e.b], dist[e.a] + e.c);
      }
    }

    bool inf = false;
    for (const Edge& e : edges) {
      if (dist[e.a] + e.c < dist[e.b]) {
        inf = true;
        break;
      }
    }

    if (inf) cout << "-inf" << nl;
    else if (dist[n+1] == 0) cout << mincost << nl;
    else cout << dist[n+1] << nl;
  }

  return 0;
}
