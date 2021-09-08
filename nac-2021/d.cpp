#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 51;
const int K = 20;

int a[N];
ll dp[K][N][N];

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, len; cin >> n >> len;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a, a+n);
  memset(dp, 0, sizeof dp);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      dp[2][i][j] = 1;
    }
  }
  for (int s = 3; s <= len; s++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i; j++) {
        for (int k = 0; k < j; k++) {
          if (a[i] <= a[j] + a[k]) {
            dp[s][i][j] += dp[s-1][j][k];
          }
        }
      }
    }
  }
  if (len == 1) {
    cout << n << endl;
  } else {
    ll ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i; j++) {
        ans += dp[len][i][j];
      }
    }
    cout << ans << endl;
  }
  return 0;
}