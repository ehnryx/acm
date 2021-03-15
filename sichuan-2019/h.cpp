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
  int n, m;
  cin >> n >> m;
  vector<int> t(n);
  for(int i=0; i<n; i++) {
    cin >> t[i];
  }
  sort(t.begin(), t.end());
  vector<int> order;
  for(int i=0; i<m; i++) {
    int c;
    cin >> c;
    if(c) {
      order.push_back(c);
    }
  }
  sort(order.begin(), order.end());

  ll ans = 0;
  int j = -1;
  for(int c : order) {
    ans += 20 * (c-1) + t[j += c];
  }
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
