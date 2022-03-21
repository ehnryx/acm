#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const int N = 25;
int a[N];
int dp[1 << N];

int solve(int bm) {
  if(bm == 0 || __builtin_popcount(bm) < 3) return 0;
  if(dp[bm] != -1) return dp[bm];
  int i = __builtin_ctz(bm);
  int ans = solve(bm ^ 1 << i);
  for(int j=i+1; j<N; j++) {
    if(!(bm & 1<<j)) continue;
    for (int k = j+1; k<N; k++) {
      if(!(bm & 1<<k)) continue;
      if(a[i] ^ a[j] ^ a[k]) continue;
      ans = max(ans, 1 + solve(bm ^ 1<<i ^ 1<<j ^ 1<<k));
    }
  }
  return dp[bm] = ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }

  int mask = (1 << n) - 1;
  memset(dp, -1, sizeof dp);

  int ans = numeric_limits<int>::max();
  for(int i=0; i<n; i++) {
    ans = min(ans, solve(mask ^ 1 << i));
  }
  cout << ans + 1 << nl;

  return 0;
}
