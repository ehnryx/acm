//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC target("sse4,avx2,abm,fma")
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
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 40;
const int M = 400 + 1;
int dp[N][N][M][10];
int split[N][N][M][10];

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  vector<string> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }

  memset(dp, INF, sizeof dp);
  for(int i=0; i<n; i++) {
    for(int j=i; j<n; j++) {
      dp[i][j][m][9] = 0;
    }
  }

  for(int len=0; len<n; len++) {
    for(int i=0; i+len<n; i++) {
      int j = i+len;
      for(int k=m-1; k>=0; k--) {
        for(int d=0; d<10; d++) {
          if(d > 0 && dp[i][j][k][d-1] < dp[i][j][k][d]) {
            dp[i][j][k][d] = dp[i][j][k][d-1];
            split[i][j][k][d] = j+1;
          }
          int cost = 0;
          for(int s=j; s>=i; s--) {
            cost += (a[s][k] - '0' != d);
            if(s > i && d > 0) {
              int cur = dp[i][s-1][k][d-1] + dp[s][j][k+1][9] + cost;
              if(cur < dp[i][j][k][d]) {
                dp[i][j][k][d] = cur;
                split[i][j][k][d] = s;
              }
            }
          }
          if(dp[i][j][k+1][9] + cost < dp[i][j][k][d]) {
            dp[i][j][k][d] = dp[i][j][k+1][9] + cost;
            split[i][j][k][d] = i;
          }
        }
      }
    }
  }

  function<void(int,int,int,int)> recover = [&](int i, int j, int k, int d) {
    if(k == m || i > j) return;
    int s = split[i][j][k][d];
    for(int t=s; t<=j; t++) {
      a[t][k] = d + '0';
    }
    recover(i, s-1, k, d-1);
    recover(s, j, k+1, 9);
  };
  recover(0, n-1, 0, 9);

  for(int i=0; i<n; i++) {
    cout << a[i] << nl;
  }

  return 0;
}

