#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';


int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n;
  cin >> n;
  while(n--) {
    int v, e;
    cin >> v >> e;
    cout << 2 - v + e << nl;
  }

  return 0;
}
