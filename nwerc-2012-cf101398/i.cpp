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

const int N = 2018;
namespace SAT {
  int low[N], vis[N], scomp[N], scompNum, I;
  vector<int> adj[N]; stack<int> verts;
  void scc(int u) { low[u] = vis[u] = ++I; verts.push(u);
    for (int v : adj[u]) {
      if (!vis[v]) scc(v);
      if (scomp[v] == -1) low[u] = min(low[u], low[v]);
    }
    if (vis[u] <= low[u]) { int v;
      do { v=verts.top(); verts.pop(); scomp[v] = scompNum; } while (v != u);
      ++ scompNum;
    }
  }
  void get_scc(int n) { memset(vis,0,sizeof vis); memset(scomp,-1,sizeof scomp);
    scompNum=I=0; for (int i = 0; i < n; i++) if (!vis[i]) scc(i);
  }

  bool truth[N/2];
  void add_clause(int a, int b) { adj[a].push_back(b); }
  bool two_sat(int n) { get_scc(n);
    for (int i=0; i<n; i+=2) {
      if (scomp[i] == scomp[i^1]) return false;
      truth[i/2] = (scomp[i] < scomp[i^1]);
    }
    return true;
  }

  void init(int n) {
    for (int i = 0; i < 2*n; i++) adj[i].clear();
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  while (cin >> n >> m) {
    SAT::init(n);

    int a, b;
    for (int i = 0; i < m; i++) {
      cin >> a >> b;
      if (a < 0) a = 2*(abs(a)-1) + 1;
      else a = 2*(a-1);
      if (b < 0) b = 2*(abs(b)-1) + 1;
      else b = 2*(b-1);
      SAT::add_clause(a^1, b);
      SAT::add_clause(b^1, a);
    }
    SAT::add_clause(0^1, 0);

    cout << (SAT::two_sat(2*n) ? "yes" : "no") << nl;
  }

  return 0;
}
