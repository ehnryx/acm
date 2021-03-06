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

ll power(ll n, ll e) {
  ll r = 1;
  for(;e;e/=2) {
    if(e&1) r = r*n;
    n = n*n;
  }
  return r;
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

  ll m;
  cin >> m;

  for(int n=3; clock()<0.9*CLOCKS_PER_SEC; n++) {
    int lim = pow(m, (ld)1/(n-1));
    ll cur = m;
    int last = 0;
    for(int i=1; i<=lim; i++) {
      ll layer = power(i, n-1);
      if(layer > cur) break;
      cur -= layer;
      last = i;
    }
    if(cur == 0) {
      cout << n << " " << last << nl;
      return 0;
    }
  }

  cout << "impossible" << nl;

  return 0;
}
