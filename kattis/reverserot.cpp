#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  string a = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_.";

  int r;
  string s;
  while(cin >> r >> s) {
    vector<int> t;
    for(char c : s) {
      t.push_back(((find(begin(a), end(a), c) - begin(a)) + r) % 28);
    }
    reverse(begin(t), end(t));
    for(int c : t) {
      cout << a[c];
    }
    cout << nl;
  }

  return 0;
}
