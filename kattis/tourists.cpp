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

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;

  const int L = 18;
  vector<vector<int>> adj(n + 1);
  vector anc(n + 1, vector<int>(L));
  vector<int> depth(n + 1);

  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

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
    return anc[a][0];
  };

  ll ans = 0;
  for(int i=1; i<=n; i++) {
    for(int j=2*i; j<=n; j+=i) {
      int c = lca(i, j);
      ans += depth[i] + depth[j] - 2*depth[c] + 1;
    }
  }
  cout << ans << nl;

  return 0;
}
