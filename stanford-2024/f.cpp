#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  map<int, int> sum, diff;
  map<pair<int, int>, int> both;
  for (int i = 0; i < n; i++) {
    int a, b;
    cin >> a >> b;
    sum[a + b] += 1;
    diff[a - b] += 1;
    both[pair(a, b)] += 1;
  }
  ll bad = 0;
  for (auto [_, v] : sum) {
    bad += (ll)v * (v - 1) / 2;
  }
  for (auto [_, v] : diff) {
    bad += (ll)v * (v - 1) / 2;
  }
  for (auto [_, v] : both) {
    bad -= (ll)v * (v - 1) / 2;
  }
  cout << (ll)n * (n - 1) / 2 - bad << nl;

  return 0;
}
