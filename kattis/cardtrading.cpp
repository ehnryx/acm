#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"

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

  int n, t, k;
  cin >> n >> t >> k;
  vector<int> cost(t);
  for(int i=0; i<n; i++) {
    int v;
    cin >> v;
    cost[v-1]++;
  }

  ll ans = 0;
  for(int i=0; i<t; i++) {
    int a, b;
    cin >> a >> b;
    ans += (ll)cost[i] * b;
    cost[i] = min(cost[i], 2);
    cost[i] = cost[i] * b + (2 - cost[i]) * a;
  }

  sort(begin(cost), end(cost));
  ans -= accumulate(begin(cost), begin(cost) + k, (ll)0);

  cout << ans << nl;

  return 0;
}
