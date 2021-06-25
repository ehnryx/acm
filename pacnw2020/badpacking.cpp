#include <bits/stdc++.h>
using namespace std;


const char nl = '\n';
using ll = long long;
using ld = long double;


int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, c;
  cin >> n >> c;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(begin(a), end(a), greater<>());

  vector<int> skip(c + 1, -1);
  skip[0] = 0;
  for (int i = 0; i < n; i++) {
    for (int v = c; v >= 0; v--) {
      // skip ith
      if (skip[v] != -1) {
        skip[v] = i + 1;
      }
      // take ith
      if (a[i] <= v && skip[v - a[i]] != -1) {
        skip[v] = skip[v - a[i]];
      }
    }
  }

  for (int v = 0; v <= c; v++) {
    if (skip[v] == -1) continue;
    if(skip[v] == 0 || a[skip[v] - 1] > c - v) {
      cout << v << nl;
      return 0;
    }
  }
  assert(false);

  return 0;
}
