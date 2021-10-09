#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 5e3+1;
ll dp[N][N];
ll sum[N][N], ksum[N][N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int s, b;
  cin >> s >> b;
  for(int i=1; i<=s; i++) {
    dp[i][0] = 1;
    for(int j=1; j<=b-s; j++) {
      //for(int k=1; k<=i; k++) { if(k<=j) dp[i][j] += (i+1-k)*dp[k][j-k]; }
      if(i<=j) {
        sum[i][j] = (sum[i-1][j] + dp[i][j-i]) % MOD;
        ksum[i][j] = (ksum[i-1][j] + i*dp[i][j-i]) % MOD;
      } else {
        sum[i][j] = sum[i-1][j];
        ksum[i][j] = ksum[i-1][j];
      }
      dp[i][j] = ((i+1)*sum[i][j] - ksum[i][j]) % MOD;
    }
  }
  cout << (dp[s][b-s] + MOD) % MOD << nl;

  return 0;
}
