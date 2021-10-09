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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e3;
vector<int> adj[N];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  for(int i=0; i<n*(n-1)/2; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].emplace_back(c);
    adj[b].emplace_back(c);
  }

  ll ans = 0;
  for(int i=1; i<=n; i++) {
    sort(adj[i].begin(), adj[i].end());
    for(int j=0; j<adj[i].size(); j+=2) {
      ans += max(adj[i][j], adj[i][j^1]);
    }
  }
  cout << ans << nl;

  return 0;
}
