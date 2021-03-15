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

const int N = 1e4 + 1;
pair<int,int> ans[N];
vector<int> adj[N];
int solve(int u, int p, int pval, int cur) {
  ans[u] = pair(pval, ++cur);
  int cval = cur;
  int other = pval;
  for(int v : adj[u]) {
    if(v == p) continue;
    cur = solve(v, u, cval, cur);
    swap(cval, other);
  }
  return cur;
}

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
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  solve(1, 0, 0, 0);
  for(int i=1; i<=n; i++) {
    if(adj[i].size() == 1) ans[i] = ans[adj[i][0]];
    cout << ans[i].first << " " << ans[i].second << nl;
  }

  return 0;
}
