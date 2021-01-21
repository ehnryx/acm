#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int x, y;
  cin >> x >> y;

  if (x > 0 && y > 0) {
    cout << 1 << nl;
  } else if (x < 0 && y > 0) {
    cout << 2 << nl;
  } else if (x < 0 && y < 0) {
    cout << 3 << nl;
  } else {
    cout << 4 << nl;
  }

  return 0;
}
