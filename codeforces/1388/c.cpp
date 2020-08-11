//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME sadcactussociety

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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 2e5 + 1;
int sz[N], h[N], good[N], bad[N];
vector<int> adj[N];

bool solve(int u, int p) {
  int gtot = 0;
  int btot = 0;
  int pop = sz[u];
  for(int v : adj[u]) {
    if(v == p) continue;
    if(!solve(v, u)) {
      return false;
    }
    sz[u] += sz[v];
    gtot += good[v];
    btot += bad[v];
  }

  int gcnt = h[u] + sz[u];
  int bcnt = sz[u] - h[u];
  if(gcnt % 2 || bcnt % 2 || gcnt < 0 || bcnt < 0 || bcnt/2 > btot + pop) {
    return false;
  }

  good[u] = gcnt / 2;
  bad[u] = bcnt / 2;
  return true;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
/*
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif
*/

  int T;
  for(cin >> T; T--; ) {
    int n, m;
    cin >> n >> m;
    for(int i=1; i<=n; i++) {
      cin >> sz[i];
    }
    for(int i=1; i<=n; i++) {
      cin >> h[i];
      adj[i].clear();
    }
    for(int i=1; i<n; i++) {
      int a, b;
      cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }

    if(solve(1, 0)) {
      cout << "YES" << nl;
    } else {
      cout << "NO" << nl;
    }
  }

  return 0;
}
