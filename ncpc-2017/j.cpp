#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int a, b;
  cin >> a >> b;
  if(max(a, b) == 0) {
    cout << "Not a moose" << nl;
  } else if(a == b) {
    cout << "Even " << a+b << nl;
  } else {
    cout << "Odd " << 2 * max(a, b) << nl;
  }

  return 0;
}
