#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const int N = 51, S = 21, MOD = 1e9+7;

int n, s;
string a[N];
int dp[N][N][S];

ll solve(int l, int r, int pos) {
  if (pos >= s) return l == r;
  if (dp[l][r][pos] != -1) return dp[l][r][pos];
  vector<vector<int>> dp2(n+1, vector<int>(28));
  for (int i = 0; i <= 27; i++) {
    dp2[r+1][i] = 1;
  }
  for (int i = r; i >= l; i--) {
    for (int c = 26; c >= 0; c--) {
      dp2[i][c] = dp2[i][c+1];
      for (int j = i; j <= r; j++) {
        if (c == 0 && a[j][pos] != 'a'-1) break;
        if (a[j][pos] != '?' && a[j][pos] != c+'a'-1) break;
        dp2[i][c] += solve(i, j, pos+1) * dp2[j+1][c+1] % MOD;
        if (dp2[i][c] >= MOD) dp2[i][c] -= MOD;
      }
    }
  }
  return dp[l][r][pos] = dp2[l][0];
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    s = max(s, (int)a[i].size());
  }
  for (int i = 0; i < n; i++) {
    while (a[i].size() < s) {
      a[i].push_back('a'-1);
    }
  }
  memset(dp, -1, sizeof dp);
  cout << solve(0, n-1, 0) << nl;

  return 0;
}
