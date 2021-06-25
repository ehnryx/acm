#include <bits/stdc++.h>
using namespace std;


const char nl = '\n';
using ll = long long;
using ld = long double;


int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  vector<int> cnt(n);
  for (int i = 0; i < n; i++) {
    cin >> cnt[i];
  }

  int ans = 0;
  for (int i = 0; i < m; i++) {
    int num = *max_element(begin(cnt), end(cnt));
    for (int j = 0; j < n; j++) {
      int need;
      cin >> need;
      if (need > 0) {
        num = min(num, cnt[j] / need);
      }
    }
    int cost;
    cin >> cost;
    ans = max(ans, num * cost);
  }
  cout << ans << nl;

  return 0;
}
