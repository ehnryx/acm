//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

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

void solve() {
  int n;
  cin >> n;
  vector<int> val(n+1);
  vector<vector<int>> group(n+1);
  for(int i=1; i<=n; i++) {
    cin >> val[i];
    group[val[i]].push_back(i);
  }
  vector<vector<int>> adj(n+1);
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  static const int L = 17;
  vector anc(n+1, vector<int>(L));
  vector<int> depth(n+1);
  function<void(int,int)> build = [&](int u, int p) {
    if(p) adj[u].erase(find(adj[u].begin(), adj[u].end(), p));
    depth[u] = depth[p] + 1;
    anc[u][0] = p;
    for(int j=1; j<L; j++) {
      anc[u][j] = anc[anc[u][j-1]][j-1];
    }
    for(int v : adj[u]) {
      build(v, u);
    }
  };
  build(1, 0);

  function<int(int,int)> lca = [=](int a, int b) {
    if(depth[a] < depth[b]) swap(a, b);
    for(int j=L-1; j>=0; j--) {
      if(depth[anc[a][j]] >= depth[b]) {
        a = anc[a][j];
      }
    }
    if(a == b) return a;
    for(int j=L-1; j>=0; j--) {
      if(anc[a][j] != anc[b][j]) {
        a = anc[a][j];
        b = anc[b][j];
      }
    }
    assert(anc[a][0]);
    return anc[a][0];
  };

  vector<tuple<int,int,int>> order;
  for(int i=1; i<=n; i++) {
    if(group[i].empty()) continue;
    int u = group[i].front();
    for(int v : group[i]) {
      u = lca(u, v);
    }
    order.emplace_back(depth[u], u, i);
  }
  sort(order.begin(), order.end(), greater<tuple<int,int,int>>());

  vector<bool> bad(n+1);
  vector<bool> vis(n+1);
  function<void(int)> dfs = [&](int u) {
    if(vis[u]) return;
    vis[u] = true;
    bad[val[u]] = true;
    for(int v : adj[u]) {
      dfs(v);
    }
  };

  int ans = 0;
  for(auto [_, u, v] : order) {
    if(bad[v]) continue;
    ans++;
    dfs(u);
  }

  assert(ans > 0);
  cout << ans << nl;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int T;
  cin >> T;
  for(int tt=1; tt<=T; tt++) {
    cout << "Case " << tt << ": ";
    solve();
  }

  return 0;
}
