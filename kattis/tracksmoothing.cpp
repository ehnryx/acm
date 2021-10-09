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

  int T;
  cin >> T;
  while(T--) {
    int r, n;
    cin >> r >> n;
    vector<pt> p;
    for(int i=0; i<n; i++) {
      int x, y;
      cin >> x >> y;
      p.push_back(pt(x,y));
    }
    ld d = 0;
    for(int i=0; i<n; i++) {
      int j = (i+1 == n ? 0 : i+1);
      d += abs(p[i]-p[j]);
    }
    if(d < 2*M_PIl*r) cout << "Not possible" << nl;
    else cout << (d - 2*M_PIl*r) / d << nl;
  }

  return 0;
}
