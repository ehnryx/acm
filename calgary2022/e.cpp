#include <bits/stdc++.h>
using namespace std;

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

  string s, t;
  cin >> s;
  map<char, string> remap;
  unordered_map<string, char> rev;
  int i;
  for(i = 0; cin >> t; i++) {
    if (i >= s.size() || (remap.count(s[i]) && remap[s[i]] != t)) {
      cout << "False";
      return 0;
    }
    if(rev.count(t) && rev[t] != s[i]) {
      cout << "False";
      return 0;
    }
    remap[s[i]] = t;
    rev[t] = s[i];
  }
  cout << (i == s.size() ? "True" : "False") << nl;

  return 0;
}
