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

  ld tot = 0;
  ll cnt = 0;
  for(string s; cin >> s; ) {
    if(s == "buy") {
      int x, y;
      cin >> x >> y;
      tot += (ld)x*y;
      cnt += x;
    } else if(s == "sell") {
      int x, y;
      cin >> x >> y;
      assert(cnt > 0);
      tot -= (tot/cnt) * x;
      cnt -= x;
    } else if(s == "split") {
      int x;
      cin >> x;
      cnt *= x;
    } else if(s == "merge") {
      int x;
      cin >> x;
      ll rem = cnt % x;
      if(rem) tot -= (tot/cnt) * rem;
      cnt /= x;
    } else {
      int y;
      cin >> y;
      ld all = cnt * y;
      ld profit = max((ld) 0, all - tot);
      cout << all - profit * 0.3 << nl;
    }
  }

  return 0;
}
