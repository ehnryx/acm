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

  vector<string> v;

  for(bool first = true;;) {
    v.push_back(cin.getline());
    if(v.back().empty()) {
      v.pop_back();

      if(!first) {
        cout << nl;
      }
      first = false;

      int maxlen = 0;
      for(string& s : v) {
        reverse(begin(s), end(s));
        maxlen = max(maxlen, (int)size(s));
      }
      for(string& s : v) {
        while(size(s) < maxlen) {
          s.push_back(' ');
        }
      }
      sort(begin(v), end(v));
      for(string& s : v) {
        reverse(begin(s), end(s));
        cout << s << nl;
      }

      v.clear();
      if (!cin) {
        break;
      }
    }
  }

  return 0;
}
