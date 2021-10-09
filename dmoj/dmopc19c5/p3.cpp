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

  int n, m;
  cin >> n >> m;

  ll ans = ((ll)n*(n-1)/2) * ((ll)m*(m-1)/2);

  --n; --m;
  for(int x=1; x<=n; x++) {
    for(int y=1; y<=m; y++) {
      if(__gcd(x,y) != 1) continue;
      ll cur = 0;
      for(int a=1; a<=(n+m)/(x+y); a++) {
        if(a*x > n || a*y > m) break;
        int b = min((n-a*x)/y, (m-a*y)/x);
        for(int j=1; j<=b; j++) {
          ans += (ll) (n-(a*x+j*y)+1) * (m-(a*y+j*x)+1);
          cur += (ll) (n-(a*x+j*y)+1) * (m-(a*y+j*x)+1);
        }
      }
    }
  }

  cout << ans << nl;

  return 0;
}
