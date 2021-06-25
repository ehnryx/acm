#include <bits/stdc++.h>
using namespace std;


const char nl = '\n';
using ll = long long;
using ld = long double;


int main() {
  cin.tie(0)->sync_with_stdio(0);

  string s;
  cin >> s;
  sort(begin(s), end(s));
  if (unique(begin(s), end(s)) == end(s)) {
    cout << 1 << nl;
  } else {
    cout << 0 << nl;
  }

  return 0;
}
