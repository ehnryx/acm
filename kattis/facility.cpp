#include <bits/stdc++.h>
using namespace std;

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

  int n, m, k;
  cin >> n >> m >> k;
  vector cost(n, vector<int>(m));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> cost[i][j];
      cost[i][j] = !!cost[i][j];
    }
  }
  sort(begin(cost), end(cost));
  cost.resize(unique(begin(cost), end(cost)) - begin(cost));

  if(accumulate(begin(cost.back()), end(cost.back()), 0) == m) {
    cost.pop_back();
  }

  int count = 0;
  for(const auto& v : cost) {
    count += m - accumulate(begin(v), end(v), 0);
  }

  if(count == m && size(cost) <= k) {
    cout << "yes" << nl;
  } else {
    cout << "no" << nl;
  }

  return 0;
}
