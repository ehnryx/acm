#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
%:include "utility/output.h"

using ll = long long;
using ld = long double;

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

  vector<int> all;
  for(int i=0; i<8; i++) {
    for(int j=!i; j<4; j++) {
      string s(i+j, '.');
      fill(begin(s), begin(s)+j, '_');
      sort(begin(s), end(s));
      do {
        all.push_back(i + j - 1 + i + 3*j);
      } while (next_permutation(begin(s), end(s)));
    }
  }
  sort(begin(all), end(all));
  all.resize(26);
  //cerr << ans << nl;

  vector<int> cnt(26);
  int ans = 0;
  for(string s; cin >> s; ) {
    for(char c : s) {
      if(isalpha(c)) {
        cnt[tolower(c) - 'a']++;
        ans += 3;
      }
    }
  }
  sort(begin(cnt), end(cnt), greater<>());

  for(int i=0; i<26; i++) {
    ans += cnt[i] * all[i];
  }
  cout << ans - 3 << nl;

  return 0;
}
