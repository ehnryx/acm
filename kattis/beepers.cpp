#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"

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

  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    int s, t;
    cin >> s >> t;
    int k;
    cin >> k;
    vector<pair<int, int>> v;
    for(int i=0; i<k; i++) {
      int a, b;
      cin >> a >> b;
      v.emplace_back(a, b);
    }
    sort(begin(v), end(v));

    int best = numeric_limits<int>::max();
    do {
      int ans = abs(s-v.front().first) + abs(t-v.front().second);
      ans += abs(s-v.back().first) + abs(t-v.back().second);
      for(int i=1; i<k; i++) {
        ans += abs(v[i].first-v[i-1].first) + abs(v[i].second-v[i-1].second);
      }
      best = min(best, ans);
    } while(next_permutation(begin(v), end(v)));
    cout << best << nl;
  }

  return 0;
}
