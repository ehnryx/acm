#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Edge {
  int i, t, p, d;
  int dist(int x) const {
    if (x<t+d) return -1;
    return x - ((p-(x-(t+d))%p)%p + d);
  }
};

struct Node {
  int i, d;
  bool operator < (const Node& o) const {
    return d < o.d;
  }
};

const int N = 1e5+1;
vector<Edge> adj[N];
int dist[N];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, m, s;
  cin >> n >> m >> s;
  const int S = 0;
  const int T = n-1;

  for (int i=0; i<m; i++) {
    int u,v,t,p,d;
    cin >> u >> v >> t >> p >> d;
    adj[v].push_back({u,t,p,d});
  }

  fill(dist, dist+N, -2);
  priority_queue<Node> dijk;
  dijk.push({T,s});
  while (!dijk.empty()) {
    Node cur = dijk.top();
    dijk.pop();
    if (cur.i == S) {
      cout << cur.d << nl;
      return 0;
    }
    if (dist[cur.i] == -2) {
      dist[cur.i] = cur.d;
      for (const Edge& e : adj[cur.i]) {
        if (dist[e.i] == -2) {
          dijk.push({e.i, e.dist(cur.d)});
        }
      }
    }
  }
  cout << "impossible" << nl;

  return 0;
}
