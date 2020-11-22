#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
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

const int N = 50 * 8 + 1;
const int M = 1<<18;
short dp[N][M];
bitset<M> nxt[N];
char grid[8][51];

bool valid(int bm, int v, int j, int m, int k) {
  int cnt = v + (bm >> (2*m-1) & 1);
  if(j == 0) {
    return (m == 1 ? (bm & 1) || cnt == k : true);
  }
  int other = cnt + (bm & 1) + (bm >> m & 1) + (bm >> (2*m) & 1);
  cnt += (bm & 1) + (bm >> (2*m) & 1) + (bm >> (m-1) & 1);
  if(j > 1) {
    cnt += (bm >> 1 & 1) + (bm >> (m+1) & 1) + (bm >> (2*m+1) & 1);
  }
  bool ok = ((bm >> m & 1) || cnt == k);
  ok &= (j+1 < m || (bm >> (m-1) & 1) || other == k);
  return ok;
}

int solve(int u, int bm, int n, int m, int k) {
  if(dp[u][bm] != -1) return dp[u][bm];

  static const int L = 2*m + 2;
  static const int clear = ~(1 << L);
  if(u == n*m) {
    dp[u][bm] = 0;
    for(int j=0, om=bm; j<m; j++) {
      if(!valid(om, 0, j, m, k)) {
        dp[u][bm] = (short)INF;
        break;
      }
      om = om << 1 & clear;
    }
    return dp[u][bm];
  }

  int add = (bm << 1 & clear) | 1;
  int skip = (bm << 1 & clear);
  int i = u / m;
  int j = u % m;

  int res = INF;
  if(i == 0 || valid(bm, 1, j, m, k)) {
    res = min(res, 1 + solve(u+1, add, n, m, k));
    nxt[u][bm] = 1;
  }
  if(i == 0 || valid(bm, 0, j, m, k)) {
    res = min(res, solve(u+1, skip, n, m, k));
    if(res == solve(u+1, skip, n, m, k)) {
      nxt[u][bm] = 0;
    }
  }
  return dp[u][bm] = res;
}

void recover(int u, int bm, int n, int m) {
  if(u == n*m) return;

  static const int L = 2*m + 2;
  static const int clear = ~(1 << L);
  grid[u%m][u/m] = (nxt[u][bm] ? '#' : '.');
  recover(u+1, (bm << 1 & clear) | nxt[u][bm], n, m);
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

  int n, m, k;
  cin >> n >> m >> k;

  memset(dp, -1, sizeof dp);
  cout << solve(0, 0, n, m, k) << nl;
  recover(0, 0, n, m);
  for(int i=0; i<m; i++) {
    cout << grid[i] << nl;
  }

  return 0;
}
