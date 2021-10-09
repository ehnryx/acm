#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
#define nl '\n'



int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int T; cin >> T;
  while(T--) {
    int n; cin >> n;
    for (int i = 0; i < n-1; ++i) {
      int x,y; cin >> x >> y;
    }
    cout << (n % 2 == 0 ? "Bob" : "Alice") << nl;
  }

  return 0;
}

