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
  ll l, r, y;
  cin >> l >> r >> y;

  vector<pair<ll,int>> p;
  for(int i=0; i<n; i++) {
    int x, v, h;
    cin >> x >> v >> h;
    ll dx = (h*y + v-1) / v - 1;
    p.emplace_back(x - dx, 1);
    p.emplace_back(x + dx + 1, -1);
  }
  p.emplace_back(r + 7, 0);
  sort(p.begin(), p.end());

  vector<int> ans(n+1);
  ll px = -INFLL;
  int cur = 0;
  for(auto [x, t] : p) {
    ll left = max(px, l);
    ll right = min(x, r+1);
    //cerr<<"@ "<<x<<" "<<t<<" -> "<<left<<" "<<right<<" w/ "<<cur<<nl;
    if(left < right) {
      ans[cur] += right - left;
      //cerr<<"add "<<right-left<<" to "<<cur<<nl;
    }
    cur += t;
    px = x;
  }

  partial_sum(ans.begin(), ans.end(), ans.begin());
  for(int i=0; i<=n; i++) {
    cout << ans[i] << nl;
  }

  return 0;
}
