#include <bits/stdc++.h>
using namespace std;


const char nl = '\n';
using ll = long long;
using ld = long double;


int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  string s;
  cin >> s;

  for (int i = 1; i <= n; i++) {
    string missing;
    for (int j = 1; j <= n; j++) {
      if (i == j) continue;
      missing += to_string(j);
    }
    if (missing == s) {
      cout << i << nl;
      return 0;
    }
  }
  assert(false);

  return 0;
}
