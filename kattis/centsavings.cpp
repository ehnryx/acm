#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

const int N = 2e3+1;
int p[N];

int dp[N][21][11];
int solve(int n, int d, int r) {
  int rem = (r<5 ? -r : 10-r);
  if (n<0) return rem;
  if (dp[n][d][r] != INF) return dp[n][d][r];
  int res = solve(n-1,d,(r+p[n])%10);
  if (d>0) res = min(res, solve(n-1,d-1,p[n]%10)+rem);
  return dp[n][d][r] = res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  memset(dp, INF, sizeof dp);

  int n, d;
  cin >> n >> d;
  int sum = 0;
  for (int i=0; i<n; i++) {
    cin >> p[i];
    sum += p[i];
  }
  cout << sum + solve(n-1,d,0) << '\n';

  return 0;
}
