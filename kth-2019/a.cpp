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
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n,m;
  cin>>n>>m;

  ld dp[2][1<<n];
  fill(dp[0],dp[0]+(1<<n),0);
  dp[0][(1<<n)-1] = 1;
  for(int i=0;i<m;i++) {
    int id = i%2;
    int a,b; ld p;
    cin>>a>>b>>p;
    --a; --b;
    fill(dp[id^1],dp[id^1]+(1<<n),0);
    for(int bm=0;bm<1<<n;bm++) {
      if((bm&1<<a) && (bm&1<<b)) {
        dp[id^1][bm] += (1-p) * dp[id][bm];
        dp[id^1][bm^1<<b] += p * dp[id][bm];
      } else {
        dp[id^1][bm] += dp[id][bm];
      }
    }
  }

  int last = m%2;
  for(int i=0;i<n;i++) {
    ld res = 0;
    for(int bm=0;bm<1<<n;bm++) {
      if(bm&1<<i) {
        res += dp[last][bm];
      }
    }
    cout<<res<<nl;
  }

  return 0;
}
