#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';
using ll = long long;

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  int M = 1e8;
  int ans = 0;
  for (int i = 2; i * i < M; i += 2) {
    int ub = M - i * i;
    for (int j = 1; j * j <= ub; j += 2) {
      if (gcd(i, j) > 1) continue;
      int a = abs(i * i - j * j);
      int b = 2 * i * j;
      int c = i * i + j * j;
      // generated a, b, c
      ll x = abs((ll)a * a - (ll)b * b);
      ll y = (ll)2 * a * b;
      ll z = (ll)a * a + (ll)b * b;
      __int128 area = (__int128)x * y / 2;
      if (area % 6 || area % 28) {
        ans += 1;
      }
    }
  }
  cout << ans << nl;

  return 0;
}
