#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

const char nl = '\n';



int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  int ans = 1;
  for (int i = 1; i + 1 < n; i++) {
    int cur = 1;
    for (int j = 1; j <= i; j++) {
      if (a[i - j] != a[i + j] || a[i - j] >= a[i - j + 1] || a[i + j] >= a[i + j - 1]) break;
      cur += 2;
    }
    ans = max(ans, cur);
  }
  cout << ans << nl;

  return 0;
}
