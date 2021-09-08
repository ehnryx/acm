#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

const char nl = '\n';

const int A = 26;
const int N = 100 + 1;
unsigned int adj[A][A];

unsigned int solve(int k, int start) {
  k /= 2; // divide by 0
  vector dp(k + 1, vector<unsigned int>(A, -1));
  dp[0][start] = 0;
  for (int i = 1; i <= k; i++) {
    for (int c = 0; c < A; c++) {
      for (int d = 0; d < A; d++) {
        dp[i][d] = (unsigned int)min(
          (unsigned long long)dp[i][d],
          (unsigned long long)dp[i - 1][c] + adj[c][d] + adj[d][c]);
      }
    }
  }
  return *min_element(begin(dp[k]), end(dp[k]));
}

int solve_odd(int k) {
  unsigned int ans = -1;
  for (int c = 0; c < A; c++) {
    ans = min(ans, solve(k, c));
  }
  cout << (int)ans << nl;
  return 0;
}

int solve_even(int k) {
  unsigned long long ans = -1;
  for (int c = 0; c < A; c++) {
    ans = min(ans, (unsigned long long)solve(k - 1, c) + adj[c][c]);
  }
  cout << (int)ans << nl;
  return 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k;
  cin >> n >> k;

  memset(adj, -1, sizeof adj);
  for (int i = 0; i < n; i++) {
    string s;
    int t;
    cin >> s >> t;
    adj[s.front() - 'a'][s.back() - 'a'] = t;
  }
  return k % 2 ? solve_odd(k) : solve_even(k);
}
