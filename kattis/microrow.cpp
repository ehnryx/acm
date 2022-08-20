#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "utility/output.h"

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
  vector<tuple<int, int, int>> ev;
  for(int i=0; i<n; i++) {
    int x, v;
    cin >> x >> v;
    ev.emplace_back(x, v, i);
  }
  sort(begin(ev), end(ev));

  vector<pair<int, int>> a;
  for(auto [x, v, i] : ev) {
    a.emplace_back(v, i);
  }

  vector<vector<pair<int, int>>> ans;
  for(int i=0; i<n; i++) {
    auto it = lower_bound(begin(ans), end(ans), a[i].first,
        [](const vector<pair<int, int>>& x, int v) { return v < x.back().first; });
    if(it == end(ans)) {
      ans.emplace_back(1, a[i]);
    } else {
      it->push_back(a[i]);
    }
  }

  vector<int> out(n);
  for(int i=0; i<size(ans); i++) {
    for(auto [_, j] : ans[i]) {
      out[j] = i + 1;
    }
  }
  cout << out << nl;

  return 0;
}
