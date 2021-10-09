//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace SAT {
  const int N = (2e3+1) * 2 * 3 + 1;
  int low[N],vis[N],scomp[N],scompNum,I;
  vector<int> adj[N]; stack<int> verts;
  void scc(int u) { low[u] = vis[u] = ++I; verts.push(u);
    for (int v : adj[u]) {
      if (!vis[v]) scc(v);
      if (scomp[v] == -1) low[u] = min(low[u], low[v]); }
    if (vis[u] <= low[u]) { int v;
      do { v=verts.top(); verts.pop(); scomp[v]=scompNum; }while (v != u);
      ++scompNum; }}
  void get_scc(int n) {
    memset(vis,0,sizeof vis); memset(scomp,-1,sizeof scomp);
    scompNum=I=0; for (int i=0; i<n; ++i) if (!vis[i]) scc(i); }

  bool truth[N/2];
  bool two_sat(int n) { get_scc(n);
    for (int i = 0; i < n; i += 2) { if (scomp[i] == scomp[i^1]) return 0;
      truth[i/2] = (scomp[i] < scomp[i^1]); } return 1; }
  void add_edge(int a, int b) { adj[a].push_back(b); }
}

int get(int n, int t, int f) {
  return 2 * (3*n + t) + (f^1);
}

const int N = 2e3 + 1;
bool adj[N][N];
int l, r;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a][b] = adj[b][a] = true;
  }

  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      if(i == j) continue;
      adj[i][j] = adj[i][j] ^ 1;
      if(adj[i][j]) {
        for(int k=0; k<3; k++) {
          SAT::add_edge(get(i, k, true), get(j, k, false));
        }
      }
    }
  }

  SAT::add_edge(get(1, 1, false), get(1, 1, true));
  SAT::add_edge(get(2, 2, false), get(2, 2, true));
  for(int i=1; i<=n; i++) {
    for(int j=0; j<3; j++) {
      for(int k=0; k<3; k++) {
        if(j == k) continue;
        SAT::add_edge(get(i, j, true), get(i, k, false));
      }
    }
  }

  for(int i=3; i<=n; i++) {
    if(adj[1][i] && adj[2][i]) {
      SAT::add_edge(get(i, 0, false), get(i, 0, true));
    } else if(adj[1][i]) {
      SAT::add_edge(get(i, 0, false), get(i, 2, true));
      SAT::add_edge(get(i, 2, false), get(i, 0, true));
      SAT::add_edge(get(i, 0, true), get(i, 2, false));
      SAT::add_edge(get(i, 2, true), get(i, 0, false));
    } else if(adj[2][i]) {
      SAT::add_edge(get(i, 0, false), get(i, 1, true));
      SAT::add_edge(get(i, 1, false), get(i, 0, true));
      SAT::add_edge(get(i, 0, true), get(i, 1, false));
      SAT::add_edge(get(i, 1, true), get(i, 0, false));
    } else {
      assert(false);
    }
  }

  if(!SAT::two_sat(SAT::N)) {
    cout << "impossible" << nl;
  } else {
    for(int i=1; i<=n; i++) {
      if(SAT::truth[get(i, 1, true) / 2]) {
        cout << i << " ";
      }
    }
    cout << nl;
    for(int i=1; i<=n; i++) {
      if(SAT::truth[get(i, 2, true) / 2]) {
        cout << i << " ";
      }
    }
    cout << nl;
  }

  return 0;
}
