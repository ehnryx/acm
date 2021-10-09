#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const int N = 2010;

int n;
string s, t;
int dp[N][N];

int solve(int i, int j) {
  if (i >= n) return n - j;
  if (j >= n) return n - i;
  if (dp[i][j] != -1) return dp[i][j];
  int ans = min(solve(i, j+1)+1, solve(i+1, j)+1);
  if (s[i] == t[j]) ans = min(ans, solve(i+1, j+1));
  ans = min(ans, solve(i+1, j+1)+1);
  return dp[i][j] = ans;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  mt19937 rng;
  cin >> s;
  n = s.size();
  int ocnt = 0;
  for (char c : s) ocnt += c == '1';
  if (ocnt > n/2) {
    for (int i = 0; i < n; i++) {
      cout << '0';
    }
    cout << nl;
    return 0;
  } else if (ocnt < n/2) {
    for (int i = 0; i < n; i++) {
      cout << '1';
    }
    cout << nl;
    return 0;
  }
  t = s;
  for (char& c : t) {
    if (c == '1') c = '0';
    else c = '1';
  }
  while (1) {
    memset(dp, -1, sizeof dp);
    cerr << s << " " << t << " -> " << solve(0, 0) << nl;
    if (solve(0, 0) > n/2) {
      cout << t << nl;
      return 0;
    }
    /*
    int flip = n/2 + 1 - solve(0, 0);
    for (int i = 0; i < flip; i++) {
      int j = rng()%n;
      if (t[j] == '1') t[j] = '0';
      else t[j] = '1';
    }*/
    for (int i = 0; i < n; i++) {
      t[i] = rng()%2+'0';
    }
  }

  return 0;
}
