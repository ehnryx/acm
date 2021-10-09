//#pragma GCC optimize("O3")
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
const ll MOD = 1e9+7;
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int M = 1<<16;
const int S = 1<<8;
ld dp[2][M];
ld pre[3*M+1];
ld bucket[M];
//ld lbuck[M], rbuck[M];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int k, n;
  cin >> k >> n;
  int m = 1<<k;
  dp[0][0] = 1;
  for(int i=1; i<n; i++) {
    ld p; int v;
    cin >> p >> v;
    int s = i%2;
    for(int j=0; j<m; j++) {
      dp[s][j] = dp[s^1][j] * (1-p);
      dp[s][j] += dp[s^1][(j+m-v)%m] * p;
    }
  }
  int s = (n-1)%2;
  for(int j=0; j<3*m; j++) {
    pre[j+1] = pre[j] + dp[s][j%m];
  }

  int sz = min(S, m);
  int b = m/sz;
  int ans = -1;
  ld best = -1;
  for(int t=0; t<sz; t++) {
    //cerr<<"Start w/ "<<t<<nl;
    ld cur = 0;
    for(int j=0; j<m; j++) {
      cur += dp[s][j] * __builtin_popcount((t+j) % m);
    }
    for(int j=0; j<b; j++) {
      bucket[j] = pre[sz*(b+j+1) - t] - pre[sz*(b+j) - t];
      //cerr<<"bucket "<<j<<" -> "<<bucket[j]<<nl;
    }

    ld init = cur;
    for(int i=0; i<b; i++) {
      //cerr<<"shift "<<i<<" w/ "<<cur<<nl;
      if(cur > best) {
        ans = t + i*sz;
        best = cur;
      }
      for(int j=0; j<b; j++) {
        int id = (j + b-i) % b;
        if(j%2 == 0) {
          cur += bucket[id];
        } else {
          int sub = __builtin_ctz((j+1)/2);
          cur -= sub * bucket[id];
        }
      }
      cur -= bucket[(b-1 + b-i) % b];
    }
    assert(abs(init - cur) < EPS);
    //cerr<<"got ans "<<ans<<" w/ "<<best<<nl;
  }

  assert(ans != -1);
  cout << ans << nl;
  //cerr<<"expect = "<<best<<nl;

  return 0;
}
