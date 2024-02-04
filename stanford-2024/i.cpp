#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

constexpr int mod = 1e9 + 7;

auto mod_add(int a, int b) -> int {
  return a + b < mod ? a + b : a + b - mod;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  auto a = vector<int>(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  auto parts = vector<vector<int>>(m + 1);
  for (int len = 0; len <= m; len++) {
    for (int bm = 0; bm < 1 << len; bm++) {
      bool ok = true;
      for (int j = 0; j < len - 1; j++) {
        ok &= ((bm >> j & 0b11) != 0b11);
      }
      if (ok) {
        parts[len].push_back(bm);
      }
    }
  }

  auto states = vector<vector<int>>(m);
  for (int j = 0; j < m; j++) {
    for (int lm : parts[j]) {
      for (int rm : parts[m - j]) {
        states[j].push_back(lm << (m - j) | rm);
      }
    }
  }

  auto dp = vector<int>(1 << m);
  auto ndp = vector<int>(1 << m);

  dp[0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int bm : states[j]) {
        if (not(bm & 1) and (j == 0 or not(bm >> (m - 1) & 1))) {
          // can light up current window:
          // bottom window is dark, previous window is dark
          int const nm = bm >> 1 | 1 << (m - 1);
          ndp[nm] = mod_add(ndp[nm], dp[bm]);
        }
        {
          // don't light up current window
          int const nm = bm >> 1;
          ndp[nm] = mod_add(ndp[nm], dp[bm]);
        }
      }
      // clear dp table for valid states, prepare for next profile
      for (int bm : states[j]) {
        dp[bm] = 0;
      }
      swap(dp, ndp);
    }
    // check that dp satisfies number of lit windows constraint
    for (int bm = 0; bm < 1 << m; bm++) {
      if (popcount((unsigned)bm) != a[i]) {
        dp[bm] = 0;
      }
    }
  }

  int ans = 0;
  for (int bm = 0; bm < 1 << m; bm++) {
    ans = mod_add(ans, dp[bm]);
  }
  cout << ans << nl;

  return 0;
}
