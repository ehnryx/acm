#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  auto c = vector<int>(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> c[i];
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int best = c[i];
    for (int j = 1; j < 7 and i - j > 0; j++) {
      best = min(best, c[i - j]);
    }
    ans += best;
  }
  cout << ans << nl;

  return 0;
}
