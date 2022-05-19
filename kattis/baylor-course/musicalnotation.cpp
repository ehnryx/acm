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

  vector<string> ans = {
    "G: ",
    "F: ",
    "E: ",
    "D: ",
    "C: ",
    "B: ",
    "A: ",
    "g: ",
    "f: ",
    "e: ",
    "d: ",
    "c: ",
    "b: ",
    "a: ",
  };
  string column = " - - - - -   -";
  assert(size(ans) == size(column));

  int n;
  cin >> n;

  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    char note = s[0];
    int duration = (s.size() == 1 ? 1 : stoi(s.substr(1)));
    if(i) {
      for(int j=0; j<size(ans); j++) {
        ans[j].push_back(column[j]);
      }
    }
    while(duration--) {
      for(int j=0; j<size(ans); j++) {
        ans[j].push_back(column[j]);
        if(ans[j][0] == note) {
          ans[j].back() = '*';
        }
      }
    }
  }

  for(const string& s : ans) {
    cout << s << nl;
  }

  return 0;
}
