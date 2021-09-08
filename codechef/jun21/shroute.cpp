#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;
  while (T--) {
    int n, m;
    cin >> n >> m;
    vector<int> dir(n + 1), ans(n + 1, n + 1);
    ans[1] = 0;

    for (int i = 1, last = -1; i <= n; i++) {
      cin >> dir[i];
      if (dir[i] == 1) {
        last = i;
      }
      if (last != -1) {
        ans[i] = min(ans[i], i - last);
      }
    }

    for (int i = n, last = -1; i > 0; i--) {
      if (dir[i] == 2) {
        last = i;
      }
      if (last != -1) {
        ans[i] = min(ans[i], last - i);
      }
      if (ans[i] > n) {
        ans[i] = -1;
      }
    }

    for (int i = 0; i < m; i++) {
      int to;
      cin >> to;
      cout << ans[to] << " ";
    }
    cout << nl;
  }

  return 0;
}