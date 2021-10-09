//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 2e5 + 1;
vector<int> adj[N];
int par[N];
int depth[N];
int sub[N];
int val[N];
int deg[N];

void build(int u, int p) {
  depth[u] = depth[p] + 1;
  par[u] = p;
  for(int v : adj[u]) {
    if(v == p) continue;
    build(v, u);
    deg[v]--;
  }
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, k;
  cin >> n >> k;
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
    deg[a]++;
    deg[b]++;
  }
  depth[0] = -1;
  build(1, 0);

  priority_queue<pair<int,int>> dijk;
  for(int i=1; i<=n; i++) {
    val[i] = depth[i];
    if(deg[i] == 0) {
      dijk.push(make_pair(val[i], i));
    }
  }
  ll ans = 0;
  while(!dijk.empty() && k > 0) {
    auto [d, u] = dijk.top();
    dijk.pop();
    if(deg[u] || d != val[u]) continue;
    ans += d;
    --k;
    sub[par[u]] += sub[u] + 1;
    if(depth[par[u]] - sub[par[u]] < val[par[u]]) {
      val[par[u]] = depth[par[u]] - sub[par[u]];
      dijk.push(make_pair(val[par[u]], par[u]));
    }
    deg[par[u]]--;
  }
  cout << ans << nl;

  return 0;
}
