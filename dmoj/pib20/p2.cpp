//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  ll T;
  cin >> T;
  ll l = 0;
  ll r = 20*T;
  while(l<r) {
    ll m = (l+r+1)/2;
    if(m/2 - m/7 <= T) {
      l = m;
    } else {
      r = m-1;
    }
  }

  const int M = 1e3;
  ll ans = r;
  for(ll i=r; i<=r+M; i++) {
    if(i/2 - i/7 <= T) {
      ans = i;
    }
  }
  cout << ans << nl;

  return 0;
}
