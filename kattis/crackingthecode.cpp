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

  const int M = 26;

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    auto ss = cin.read<string>(n);
    string s;
    cin >> s;
    map<char, set<char>> all;
    for(const string& t : ss) {
      if(size(t) != size(s)) continue;
      vector<char> f(M), b(M);
      bool bad = false;
      for(int i=0; i<size(t); i++) {
        if(f[s[i] - 'a'] && f[s[i] - 'a'] != t[i]) {
          bad = true;
          break;
        }
        if(b[t[i] - 'a'] && b[t[i] - 'a'] != s[i]) {
          bad = true;
          break;
        }
        f[s[i] - 'a'] = t[i];
        b[t[i] - 'a'] = s[i];
      }
      if(bad) continue;

      // only missing one ?
      vector<int> zero;
      int x = 0;
      for(int i=0; i<M; i++) {
        if(!b[i]) zero.push_back(i);
        x ^= (i + 'a') ^ b[i];
      }
      if(size(zero) == 1) {
        b[zero[0]] = x;
      }

      for(int i=0; i<M; i++) {
        all[i + 'a'].insert(b[i]);
      }
    }

    string w;
    cin >> w;
    for(char& c : w) {
      if(all[c].empty()) {
        w = "IMPOSSIBLE";
        break;
      }
      if(all[c].size() == 1) {
        c = *all[c].begin();
        if(!c) c = '?';
      } else {
        c = '?';
      }
    }
    cout << w << nl;
  }

  return 0;
}
