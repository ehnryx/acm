//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "brick"

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

const int N = 9;
ll dp[N][1<<(2*N)];

vector<function<bool(int,int)>> valid = {
  [](int bm, int lo) -> bool {
    for(int i=0; i<N; i++) {
      if(!(bm>>N & 1<<i)) continue;
      bool ok = false;
      if(i > 0 && (lo & 1<<i) && (lo & 1<<(i-1))) ok = true;
      if((lo & 1<<i) && (bm & 1<<i) && (i == 0 || !(bm & 1<<(i-1)))) ok = true;
      if(i > 0 && (lo & 1<<(i-1)) && (bm & 1<<(i-1)) && !(bm & 1<<i)) ok = true;
      if(i > 0 && (lo & 1<<i) && (bm>>N & 1<<(i-1))) ok = true;
      if(i+1 < N && i > 0 && (lo & 1<<(i-1)) && (bm>>N & 1<<(i+1))) ok = true;
      if(!ok) return false;
    }
    return true;
  },
  [](int bm, int lo) -> bool {
    for(int i=0; i<N; i++) {
      if(!(bm>>N & 1<<i)) continue;
      if(i+1 == N) return false;
      bool ok = false;
      if((lo & 1<<i) && (lo & 1<<(i+1))) ok = true;
      if((lo & 1<<i) && (bm & 1<<i) && !(bm & 1<<(i+1))) ok = true;
      if((lo & 1<<(i+1)) && (bm & 1<<(i+1)) && !(bm & 1<<i)) ok = true;
      if(i > 0 && (lo & 1<<(i+1)) && (bm>>N & 1<<(i-1))) ok = true;
      if(i+1 < N && (lo & 1<<i) && (bm>>N & 1<<(i+1))) ok = true;
      if(!ok) return false;
    }
    return true;
  },
};

ll solve(int m, int n) {
  memset(dp, 0, sizeof dp);
  int full = (1<<m)-1;
  dp[0][full|(full<<1|1)<<N] = 1;

  for(int i=1; i<=n; i++) {
    for(int bm=0; bm<1<<(2*N); bm++) {
      for(int lo=0; lo<1<<N; lo++) {
        int sm = bm >> N | lo << N;
        if(dp[i-1][sm] && valid[i%2](bm, lo)) {
          dp[i][bm] += dp[i-1][sm];
        }
      }
    }
  }

  ll ans = 0;
  for(int bm=1; bm<1<<N; bm++) {
    ans += dp[n][bm<<N];
  }
  return ans;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int mm, nn;
  cin >> mm >> nn;
  for(int m=1; m<=mm; m++) {
    for(int n=1; n<=nn; n++) {
      printf("dp[%d][%d] = %lld;\n", m, n, solve(m, n));
    }
  }

  return 0;
}
