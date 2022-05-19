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
  auto all = cin.read<int>(n);
  sort(begin(all), end(all));
  int l, r;
  cin >> l >> r;
  if(l % 2 == 0) l++;
  if(r % 2 == 0) r--;

  pair<int, int> best(0, 0);
  for(int i=1; i<n; i++) {
    int mid = (all[i] + all[i-1]) / 2;
    int dist = (all[i] - all[i-1]) / 2;
    for(int x=-1; x<=1; x++) {
      if((mid + x) % 2 && l <= mid + x && mid + x <= r) {
        best = max(best, pair(dist - abs(x), mid + x));
      }
    }
  }

  int dl = 1e9;
  int dr = 1e9;
  for(int x : all) {
    dl = min(dl, abs(x - l));
    dr = min(dr, abs(x - r));
  }
  best = max(best, pair(dl, l));
  best = max(best, pair(dr, r));

  cout << best.second << nl;

  return 0;
}
