#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;

const int N = 1e5+10, M = 105;

string s, t;
int dp[N][M];

int solve(int i, int j) {
  if (j >= t.size()) return i-1;
  if (i >= s.size()) return i;
  if (dp[i][j] != -1) return dp[i][j];
  if (s[i] == t[j]) return dp[i][j] = solve(i+1, j+1);
  return dp[i][j] = solve(i+1, j);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> s >> t;
  memset(dp, -1, sizeof dp);
  ll ans = 0;
  for (int i = 0; i < s.size(); i++) {
    ans += (int)s.size() - solve(i, 0);
  }
  cout << ans << nl;

  return 0;
}
