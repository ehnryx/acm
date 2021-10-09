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



// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  int L, R, X, Y;
  cin >> L >> R >> X >> Y;

  function<ld(int,int)> get_point = [=](int a, int b) {
    return X - (ld)Y*(X-a)/(Y-b);
  };

  vector<pair<ld,int>> p;
  for(int i=0; i<n; i++) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    ld s = max((ld)L, min((ld)R, get_point(a, b)));
    ld t = max((ld)L, min((ld)R, get_point(x, y)));
    if(abs(s - t) < EPS) continue;
    if(s > t) swap(s, t);
    p.push_back(make_pair(s, 1));
    p.push_back(make_pair(t, -1));
  }
  sort(p.begin(), p.end());

  ld ans = 0;
  ld px = L;
  int cur = 0;
  for(auto [x, t] : p) {
    if(cur == 0) {
      ans += x - px;
    }
    cur += t;
    px = x;
  }
  ans += R - px;
  cout << ans << nl;

  return 0;
}
