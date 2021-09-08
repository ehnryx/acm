#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

const char nl = '\n';

const int A = 26;
const int N = 100 + 1;
const int BAD = -2;
int adj[A][A];
int dp[N][A];

int solve(int k, int c) {
  if (dp[k][c] != -1) {
    return dp[k][c];
  }
  if (k == 0) {
    return 0;
  }
  int ans = BAD;
  for (int d = 0; d < A; d++) {
    if (adj[c][d] != -1 && adj[d][c] != -1) {
      int res = solve(k-1, d);
      if (res != BAD) {
        res += adj[c][d] + adj[d][c];
        ans = ans == BAD ? res : min(ans, res);
      }
    }
  }
  return dp[k][c] = ans;
}

int solve_odd(int k) {
  int ans = -1;
  for (int c = 0; c < A; c++) {
    int res = solve(k-1, c);
    if (res != BAD) {
      ans = ans == -1 ? res : min(ans, res);
    }
  }
  cout << ans << nl;
  return 0;
}

int solve_even(int k) {
  int ans = -1;
  for (int c = 0; c < A; c++) {
    if (adj[c][c] != -1) {
      int res = solve(k-1, c);
      if (res != BAD) {
        res += adj[c][c];
        ans = ans == -1 ? res : min(ans, res);
      }
    }
  }
  cout << ans << nl;
  return 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k;
  cin >> n >> k;

  memset(adj, -1, sizeof adj);
  memset(dp, -1, sizeof dp);
  for (int i = 0; i < n; i++) {
    string s;
    int t;
    cin >> s >> t;
    adj[s.front() - 'a'][s.back() - 'a'] = t;
  }
  return (k % 2 == 1) ? solve_odd(k/2+1) : solve_even(k/2);
}
