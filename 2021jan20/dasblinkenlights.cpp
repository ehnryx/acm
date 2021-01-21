#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int p, q, s;
  cin >> p >> q >> s;
  for(int i=1; i<=s; i++) {
    if(i % p == 0 && i % q == 0) {
      cout << "yes" << nl;
      return 0;
    }
  }
  cout << "no" << nl;

  return 0;
}
