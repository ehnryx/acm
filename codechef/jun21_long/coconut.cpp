#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;
  while (T--) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    cout << (x + a - 1) / a + (y + b - 1) / b << nl;
  }

  return 0;
}