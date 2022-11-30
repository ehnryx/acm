#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

int _(int v) {
  return v - '0';
}

bool solve(string s, int i, string& ans) {
  if(i == size(s)) return true;
  for(int d=0; d<10; d++) {
    if(i < size(ans)) {
      ans[i] = d + '0';
    } else if(d > 0) {
      break;
    }
    int sum = 0;
    for(int j=0; j<size(ans); j++) {
      int k = i - j;
      if(k < 0 || size(ans) <= k) continue;
      sum = (sum + _(ans[j]) * _(ans[k])) % 10;
    }
    if(sum == _(s[i]) && solve(s, i + 1, ans)) {
      return true;
    }
  }
  return false;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  string s;
  cin >> s;
  if(size(s) % 2 == 0) {
    cout << -1 << nl;
    return 0;
  }

  string ans((size(s) + 1) / 2, 0);
  if(solve(s, 0, ans)) {
    cout << ans << nl;
  } else {
    cout << -1 << nl;
  }

  return 0;
}
