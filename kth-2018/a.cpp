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

  int n,m,c;
  cin>>n>>m>>c;
  unordered_map<string,int> idx;
  string s[n];
  for(int i=0;i<n;i++) {
    cin>>s[i];
    idx[s[i]] = i;
  }
  bool bad[n][n];
  memset(bad,0,sizeof bad);
  for(int i=0;i<m;i++) {
    string a,b;
    cin>>a>>b;
    bad[idx[a]][idx[b]] = true;
    bad[idx[b]][idx[a]] = true;
  }

  bool good[1<<n];
  for(int bm=0;bm<1<<n;bm++) {
    good[bm] = (__builtin_popcount(bm) <= c);
    for(int i=0;i<n;i++) {
      if(!(bm&1<<i)) continue;
      for(int j=0;j<i;j++) {
        if(!(bm&1<<j)) continue;
        good[bm] &= !bad[i][j];
      }
    }
  }

  int dp[1<<n];
  int pre[1<<n];
  memset(dp,INF,sizeof dp);
  dp[0] = 0;
  for(int bm=1;bm<1<<n;bm++) {
    for(int sm=bm;sm;sm=(sm-1)&bm) {
      if(good[sm] && dp[bm^sm]+1 < dp[bm]) {
        dp[bm] = dp[bm^sm]+1;
        pre[bm] = bm^sm;
      }
    }
  }

  cout<<dp[(1<<n)-1]<<nl;
  for(int bm=(1<<n)-1;bm;bm=pre[bm]) {
    for(int i=0;i<n;i++) {
      if((bm^pre[bm])&1<<i) {
        cout<<s[i]<<" ";
      }
    }
    cout<<nl;
  }

  return 0;
}
