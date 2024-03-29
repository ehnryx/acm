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
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  ll cur = 1;
  bool over = false;
  for(int i=0; i<n; i++) {
    ll a;
    cin >> a;
    if(over) {
      cur = (cur*2 - a) % MOD;
    } else {
      cur = cur*2 - a;
      if(cur < 0) {
        cout << "error" << nl;
        return 0;
      }
      if(cur > 1LL<<60) {
        over = true;
      }
    }
  }
  cout << (cur % MOD + MOD) % MOD << nl;

  return 0;
}
