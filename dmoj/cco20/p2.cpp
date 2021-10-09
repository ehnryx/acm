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
  vector<pair<int,int>> v;
  for(int i=1; i<=n; i++) {
    int a;
    cin >> a;
    v.emplace_back(a, i);
  }
  sort(v.begin(), v.end(), greater<pair<int,int>>());

  set<int> active;
  vector<int> res(n+1);
  for(int i=n, j=0; i>=1; i--) {
    while(j < n && v[j].first >= i) {
      active.insert(v[j].second);
      j++;
    }
    if(active.empty()) {
      cout << -1 << nl;
      return 0;
    }
    res[i] = *active.rbegin();
    active.erase(prev(active.end()));
  }

  ll ans = 0;
  ordered_set<int> seen;
  for(int i=n; i>=1; i--) {
    ans += seen.order_of_key(res[i]);
    seen.insert(res[i]);
  }
  cout << ans << nl;

  return 0;
}
