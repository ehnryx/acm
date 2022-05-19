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

  int n;
  cin >> n;
  if(n != 52/2) {
    cout << (n < 52/2 ? "im" : "") << "possible" << nl;
    return 0;
  }

  vector<int> cnt(128), maxv(128);
  for(int i=0; i<n; i++) {
    int v; char c;
    cin >> v >> c;
    cnt[c]++;
    maxv[c] = max(maxv[c], v);
  }

  for(char c : "CDHS"s) {
    if(maxv[c] > cnt[c]) {
      cout << "possible" << nl;
      return 0;
    }
  }

  cout << "impossible" << nl;

  return 0;
}
