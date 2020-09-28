//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

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

const int N = 30;
ll dp[N][1<<3];
int bad[N];

int count(int bm, int sm) {
  vector<ll> up(4);
  up[0] = 1;
  for(int i=0; i<3; i++) {
    if(sm & 1<<i) {
      up[i+1] = up[i];
    } else {
      up[i+1] = up[i];
      if(i > 0 && (bm & 1<<i) && (bm & 1<<(i-1)) && !(sm & 1<<(i-1))) {
        up[i+1] += up[i-1];
      }
    }
  }
  return up.back();
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;
  for(int i=0; i<m; i++) {
    ld x, y;
    cin >> x >> y;
    bad[(int)floor(x) + 1] |= 1 << (int)floor(y);
  }

  dp[0][0b111] = 1;
  for(int i=1; i<=n; i++) {
    for(int bm=0; bm<1<<3; bm++) {
      if((bm & bad[i]) != bad[i]) continue;
      int cm = bm ^ bad[i];
      dp[i][bm] += dp[i-1][0b111] * count(cm, 0);
      for(int sm=cm; sm; sm=(sm-1)&cm) {
        dp[i][bm] += dp[i-1][0b111^sm] * count(cm, sm);
      }
      /*
      for(int om=0; om<1<<3; om++) {
        int have = 0b111 ^ om;
        dp[i][bm] += dp[i-1][om] * count(cm, 0);
        for(int sm=have; sm; sm=(sm-1)&have) {
          dp[i][bm] += dp[i-1][om] * count(cm, cm & sm);
        }
      }
      */
    }
  }

  cout << dp[n][0b111] << nl;
  //cout << accumulate(dp[n], dp[n] + 8, (ll) 0) << nl;

  return 0;
}
