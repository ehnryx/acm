#include <bits/stdc++.h>
using namespace std;

#include "../../../lca/number/mod_int.h"

const char nl = '\n';
using ll = long long;

constexpr int MOD = 998244353;
using Int = mod_int<MOD>;

constexpr int S = 1e7;
constexpr int M = 50;
constexpr int R = 1e5 + 1;
Int prod[S + R];
vector<tuple<int,int,int>> group[M];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int r;
  cin >> r;
  Int factr = 1;
  for (int i = 2; i <= r; i++) {
    factr *= i;
  }
  factr = factr.inverse();
  int s = (r % 2 ? -1 : 1);

  int n;
  cin >> n;
  vector<int> a(n), p(n);

  vector<Int> coeff(n);
  int half = MOD / 2 + r;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i] >= MOD) a[i] -= MOD;
    if (a[i] < r) {
      // coeff is zero, pass
    } else {
      if (a[i] <= half) {
        int j = (a[i] - r) / S;
        group[j].emplace_back(a[i], 1, i);
      } else {
        int j = (MOD - a[i] - 1) / S;
        group[j].emplace_back(MOD - a[i] - 1 + r, s, i);
      }
    }
  }

  prod[0] = 1;
  for (int g = 0; g < M; g++) {
    int start = g * S;
    for (int i = 1; i < S + R; i++) {
      prod[i] = prod[i - 1] * (start + i);
    }
    for (auto [right, sign, i] : group[g]) {
      coeff[i] = prod[right - start] * prod[right - start - r].inverse();
      if (sign < 0) coeff[i] = -coeff[i];
    }
  }

  Int ans = 1;
  for (int i = 0; i < n; i++) {
    cin >> p[i];
    ans *= coeff[i] * factr * p[i] + 1 - p[i];
  }
  cout << ans << nl;

  return 0;
}