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

const int N = 30 + 2;
ld xp[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(3);

  int n; ld t;
  while(cin >> n >> t && n) {
    xp[n+1] = 1;
    for(int i=n; i>0; i--) {
      xp[i] = 0;
      ld c = 1 / (2*xp[i+1]);
      ld got = 1;
      if(c > t) {
        xp[i] += (c-t) / (1-t);
        got = (1-c) / (1-t);
      }
      c = max(c, t);
      ld p = (1./2 - c*c/2) / (1-c);
      assert(0 <= p && p <= 1);
      xp[i] += got * p * 2*xp[i+1];
    }
    cout << xp[1] << nl;
  }

  return 0;
}
