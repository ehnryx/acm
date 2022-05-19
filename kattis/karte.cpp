#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

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

  string suits = "PKHT";
  map<char, set<int>> have;

  string s = cin.getv<string>();
  for(int i=0; 3*i<size(s); i++) {
    char t = s[3*i];
    int v = stoi(s.substr(3*i + 1, 3));
    if(!have[t].insert(v).second) {
      cout << "GRESKA" << nl;
      return 0;
    }
  }

  for(char c : suits) {
    cout << 13 - have[c].size() << " ";
  }
  cout << nl;

  return 0;
}
