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
  int id, cost;
  bool operator < (const Edge& e) const {
    return cost > e.cost;
  }
};

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  for (int n,m,q,s; cin>>n>>m>>q>>s && n;) {
    vector<Edge> adj[n];
    for (int i=0; i<m; i++) {
      int a, b, c;
      cin >> a >> b >> c;
      adj[a].push_back({b,c});
    }

    vector<int> dist(n,-1);
    priority_queue<Edge> dijk;
    dijk.push({s,0});
    while (!dijk.empty()) {
      Edge cur = dijk.top();
      dijk.pop();
      if (dist[cur.id] == -1) {
        dist[cur.id] = cur.cost;
        for (const Edge& e : adj[cur.id]) {
          dijk.push({e.id, e.cost+cur.cost});
        }
      }
    }

    for (int i=0; i<q; i++) {
      cin >> s;
      if (dist[s] == -1) cout << "Impossible" << nl;
      else cout << dist[s] << nl;
    }
    cout << nl;
  }

  return 0;
}
