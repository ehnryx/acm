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

  const int M = 26;

  string all, s;
  cin >> all;
  cin >> s;

  int n = s.size();
  vector<vector<int>> idx(M);
  for(int i=0; i<n; i++) {
    idx[s[i] - 'a'].push_back(i);
  }
  for(int i=0; i<M; i++) {
    idx[i].push_back(n);
  }

  int length = 0;
  for(int at = -1; at != n; length++) {
    int to = -1;
    for (char c : all) {
      to = max(to, *upper_bound(begin(idx[c - 'a']), end(idx[c - 'a']), at));
    }
    at = to;
  }
  cerr << "length: " << length << nl;

  int T;
  cin >> T;
  while(T--) {
    string t;
    cin >> t;
    if(t.size() != length) {
      cout << 0 << nl;
    } else {
      int at = -1;
      for(char c : t) {
        at = *upper_bound(begin(idx[c - 'a']), end(idx[c - 'a']), at);
        //at = nxt[at + 1][c - 'a'];
        if(at == n) break;
      }
      cout << (at == n) << nl;
    }
  }

  return 0;
}
