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

  string s;
  cin >> s;
  vector<bool> have(26);
  for(char c : s) {
    have[c - 'a'] = true;
  }

  cin >> s;
  int n = s.size();
  vector nxt(n+1, vector<int>(26, n));
  vector<int> last(26, n);
  for(int i=n-1; i>=0; i--) {
    last[s[i] - 'a'] = i;
    nxt[i] = last;
  }

  vector dp(n+1, vector<int>(26));
  fill(begin(dp[0]), end(dp[0]), -1);
  int length = -1;
  for(int i=1; i<=n && length == -1; i++) {
    for(int c=0; c<26 && length == -1; c++) {
      if (!have[c]) continue;
      for(int d=0; d<26 && length == -1; d++) {
        if (!have[d]) continue;
        int j = dp[i-1][d] + 1;
        dp[i][c] = max(dp[i][c], nxt[j][c]);
        if(dp[i][c] == n) {
          length = i;
          break;
        }
      }
    }
  }
  cerr << "length: " << length << nl;

  int m;
  cin >> m;
  for(int i=0; i<m; i++) {
    string t;
    cin >> t;
    if (t.size() != length) {
      cout << 0 << nl;
    } else {
      int at = -1;
      for(char c : t) {
        at = nxt[at + 1][c - 'a'];
        if (at == n) break;
      }
      cout << (at == n) << nl;
    }
  }

  return 0;
}
