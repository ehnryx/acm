#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

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
  auto g = cin.read<pair<int, int>>(n);

  int m;
  cin >> m;
  auto pegs = cin.read<int>(m);

  vector<int> cnt;
  for(auto [a, b] : g) {
    auto l = lower_bound(begin(pegs), end(pegs), a);
    auto r = upper_bound(begin(pegs), end(pegs), b);
    if(r - l > 2) {
      cout << "impossible" << nl;
      return 0;
    }
    cnt.emplace_back(2 - (r - l));
  }

  vector<int> ans;
  for(int i=0; i<n; i++) {
    if(!cnt[i]) continue;
    if(i+1<n && cnt[i+1] && g[i].second == g[i+1].first) {
      auto it = lower_bound(begin(pegs), end(pegs), g[i].second);
      if(it == end(pegs) || *it != g[i].second) {
        ans.push_back(g[i].second);
        cnt[i]--;
        cnt[i+1]--;
      }
    }
    int mid = (g[i].first + g[i].second) / 2;
    for(int j=0; j<cnt[i]; j++, mid++) {
      auto it = lower_bound(begin(pegs), end(pegs), mid);
      if(it == end(pegs) || *it != mid) {
        ans.push_back(mid);
      } else {
        j--;
      }
    }
  }

  cout << ans.size() << nl;
  for(int it : ans) {
    cout << it << " ";
  }
  cout << nl;

  return 0;
}
