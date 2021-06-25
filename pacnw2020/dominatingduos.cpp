#include <bits/stdc++.h>
using namespace std;


const char nl = '\n';
using ll = long long;
using ld = long double;


int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<pair<int, int>> order;
  for (int i = 0; i < n; i++) {
    int v;
    cin >> v;
    order.emplace_back(v, i);
  }
  sort(begin(order), end(order), greater<>());

  int ans = 0;
  int left = n;
  int right = -1;
  for (auto [v, i] : order) {
    ans += 2 - (i < left) - (i > right);
    left = min(left, i);
    right = max(right, i);
  }
  cout << ans << nl;

  return 0;
}
