#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "ds/fenwick_tree.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  cin >> n;
  vector<vector<int>> index(n+1);
  fenwick_tree<int> bit(n+1);
  for(int i=1; i<=n; i++) {
    int a;
    cin >> a;
    index[a].push_back(i);
    bit.insert(i);
  }

  vector<pair<int, int>> part(n+1);
  for(int i=1; i<=n; i++) {
    for(int j : index[i]) {
      part[j].second = n-j - bit.query(j+1, n);
    }
    for(int j : index[i]) {
      bit.insert(j, -1);
    }
    for(int j : index[i]) {
      part[j].first = bit.query(1, j-1);
    }
  }

  ll ans = 0;
  for(int i=1; i<=n; i++) {
    ans += (ll)part[i].first * part[i].second;
  }
  cout << ans << nl;

  return 0;
}
