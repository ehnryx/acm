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
const ld EPS = 1e-12;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Edge {
  int id;
  ld dist;
  ll val;
  int num;
  Edge(){}
  Edge(int i, ld d, ll v, int n): id(i), dist(d), val(v), num(n) {}
  bool operator < (const Edge& o) const {
    if (abs(dist-o.dist) < EPS) return num > o.num;
    else return dist < o.dist;
  }
};

const int N = 5e4+1;
vector<Edge> adj[N];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;

  int a, b, c;
  for (int i=0; i<n; i++) {
    cin >> a >> b >> c;
    adj[a].push_back(Edge(b,(ld)c/100,c,1));
  }

  bitset<N> vis;
  priority_queue<Edge> dijk;
  dijk.push(Edge(1,1,1,0));
  while (!dijk.empty()) {
    Edge cur = dijk.top();
    dijk.pop();
    if (cur.id == n) {
      cout << cur.val << nl;
      break;
    }

    if (!vis[cur.id]) {
      vis[cur.id] = true;
      for (const Edge& e : adj[cur.id]) {
        dijk.push(Edge(e.id, e.dist*cur.dist, e.val*cur.val%MOD, cur.num+1));
      }
    }
  }

  return 0;
}
