#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 11'092'019;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  string s;
  cin >> s;
  vector<int> cnt(26);
  for(char c : s) {
    cnt[c - 'a']++;
  }
  ll ans = 1;
  for(int c : cnt) {
    ans *= c + 1;
    ans %= MOD;
  }
  cout << ans << nl;

  return 0;
}
