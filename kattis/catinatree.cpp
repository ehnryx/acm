//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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

const int N = 2e5;
int par[N];
vector<int> adj[N];

pair<int,int> solve(int u, int d) {
  int res = 0;
  vector<int> dists;
  for(int v : adj[u]) {
    auto [cnt, dist] = solve(v, d);
    dists.push_back(dist);
    res += cnt;
  }
  sort(dists.begin(), dists.end(), greater<int>());

  int last = dists.size();
  while(last >= 2 && dists[last-1] + dists[last-2] < d) {
    last--;
    res--;
  }

  int to = last ? dists[last-1] : INF;
  return to >= d ? make_pair(res + 1, 1) : make_pair(res, to + 1);
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

  int n, d;
  cin >> n >> d;
  for(int i=1; i<n; i++) {
    cin >> par[i];
    adj[par[i]].push_back(i);
  }
  cout << solve(0, d).first << nl;

  return 0;
}
