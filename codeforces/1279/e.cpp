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

const int N = 50+1;
ll dp[N][N];
ll fact[N];

ll ncr(

void precompute() {
  fact[0] = 1;
  for(int i=1; i<N; i++) {
    fact[i] = mul(fact[i-1], i);
  }

  dp[0][0] = 1;
  for(int n=1; n<N; n++) {
    for(int m=0; m<n; m++) {
      for(int g=m; g<n; g++) {
        if(g == 0) {
          dp[n][m] = add(dp[n][m], dp[n-1][0]);
        } else {
          for(int k=1; k<=g; k++) {
            ll cur = mul(ncr(g-1, k-1), fact[k]);
            dp[n][m] = add(dp[n][m], mul(cur, dp[n-k+1][g-k]));
          }
        }
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  precompute();

  return 0;
}
