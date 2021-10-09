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

  int n;
  cin >> n;
  vector<pair<int,int>> p;
  for(int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    p.push_back(make_pair(a, b));
  }
  sort(p.begin(), p.end(), greater<pair<int,int>>());
  int cur = INF;
  multiset<int> have;
  ll ans = 0;
  for(auto [a, b] : p) {
    while(!have.empty() && cur > a) {
      ans += *have.rbegin();
      have.erase(prev(have.end()));
      cur--;
    }
    cur = a;
    have.insert(b);
  }
  while(!have.empty() && cur > 0) {
    ans += *have.rbegin();
    have.erase(prev(have.end()));
    cur--;
  }
  cout << ans << nl;

  return 0;
}
